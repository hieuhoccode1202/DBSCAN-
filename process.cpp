#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <queue>
#include <cmath>
#include <tuple>
#include <ctime>

using namespace std;

struct point
{
    double x, y;
    bool operator<(const point &other) const
    {
        return tie(x, y) < tie(other.x, other.y);
    }
};

vector<point> ans;
map<point, int> color;
double eps;
int minPtr;

void read_file(string file)
{
    ifstream ss(file);
    string line;
    while (getline(ss, line))
    {
        stringstream tmp(line);
        string xtr, ytr;
        getline(tmp, xtr, ',');
        getline(tmp, ytr, ',');
        if (xtr.empty() || ytr.empty())
            continue;
        double x = stod(xtr), y = stod(ytr);
        ans.push_back({1.0 * x, 1.0 * y});
    }
}

double distance(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<point> calc_nn(point tmp)
{
    vector<point> res;
    int n = ans.size();
    for (int i = 0; i < n; ++i)
    {
        if (distance(ans[i], tmp) <= eps)
        {
            res.push_back(ans[i]);
        }
    }

    if (res.size() < minPtr - 1)
    {
        res.clear();
        return res;
    }
    return res;
}

void set_up()
{
    color.clear();
    int n = ans.size();
    int t = 1;

    for (int i = 0; i < n; ++i)
    {
        point tmp = ans[i];
        if (color.count(tmp))
            continue;

        vector<point> res = calc_nn(tmp);
        if (!res.empty())
        {
            color[tmp] = t;
            queue<point> q;
            q.push(tmp);

            while (!q.empty())
            {
                point temp = q.front();
                q.pop();

                vector<point> neighbors = calc_nn(temp);
                if (neighbors.empty())
                    continue;

                for (point p : neighbors)
                {
                    if (color.count(p) == 0)
                    {
                        color[p] = t;
                        q.push(p);
                    }
                }
            }
            ++t;
        }
    }
}

int main()
{
    clock_t start = clock();
    string file = "Moon1000.csv";
    file = "Face0.csv";
    file = "spiral500.csv";
    file = "spiral1000.csv";
    read_file(file);
    ofstream out("output.csv");
    //spiral 0.08 7
    //face 24 8
    eps = 0.08;
    minPtr = 7;
    set_up();
    out << "x y color\n";
    for (auto x : ans)
    {
        out << x.x << " " << x.y << " " << color[x] << endl;
    }
    out.close();
    cerr << "Time: " << 1000 * ((double)(clock() - start)) / CLOCKS_PER_SEC << " ms" << endl;
    system("python draw.py");
    return 0;
}
