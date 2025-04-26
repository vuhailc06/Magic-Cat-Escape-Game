#include "Utilities.h"

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
long long RandNum(long long l, long long r) { assert(l <= r); return uniform_int_distribution<long long>(l, r)(rd); }

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void paintBrush(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = -radius; w <= radius; ++w) {
        for (int h = -radius; h <= radius; ++h) {
            if (w * w + h * h <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x + w, y + h);
            }
        }
    }
}

void DrawSmoothStroke(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int radius) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = sqrtf(dx * dx + dy * dy);
    int steps = distance; 
    for (int i = 0; i <= steps; ++i) {
        float t = 1.0 * i / steps;
        int x = x1 + dx * t;
        int y = y1 + dy * t;
        paintBrush(renderer, x, y, radius);
    }
}

void SetColor(SDL_Renderer* renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

string toString(int num) {
    string s = "";
    while (num > 0) {
        s += char(num % 10 + '0');
        num /= 10;
    }
    while ((int)s.size() < 6) s += '0';
    reverse(s.begin(), s.end());
    return s;
}

bool detectRed(const vector<pair<int, int>> &points) {
    if ((int)(points.size()) == 0) return 0;
    for (auto p : points) if (abs(p.second - points[0].second) > 15) return 0;
    return 1;
}

bool detectBlue(const vector<pair<int, int>> &points) {
    if ((int)(points.size()) == 0) return 0;
    for (auto p : points) if (abs(p.first - points[0].first) > 15) return 0;
    return 1;
}

bool detectYellow(const vector<pair<int, int>> &points) {
    int peak = 0;
    for (int i = 0; i < (int)(points.size()); i++) if (points[i].second > points[peak].second) peak = i;
    if (peak <= 1 || peak >= (int)(points.size()) - 2) return 0;
    for (int i = 0; i < min((int)(points.size()) - 1, peak) ; i++) if (points[i].second > points[i + 1].second) return 0;
    for (int i = peak; i < (int)(points.size()) - 1; i++) if (points[i].second < points[i + 1].second) return 0;
    return 1;
}

bool detectGreen(const vector<pair<int, int>> &points) {
    int peak = 0;
    for (int i = 0; i < (int)(points.size()); i++) if (points[i].second < points[peak].second) peak = i;
    if (peak <= 1 || peak >= (int)(points.size()) - 2) return 0;
    for (int i = 0; i < min((int)(points.size()) - 1, peak); i++) if (points[i].second < points[i + 1].second) return 0;
    for (int i = peak; i < (int)(points.size()) - 1; i++) if (points[i].second > points[i + 1].second) return 0;
    return 1;
}

bool detectHeart(const vector<pair<int, int>> &points) {
    if ((int)points.size() < 3) return 0;
    if (distance(points[0].first, points[0].second, points.back().first, points.back().second) <= 15) return 1;
    return 0;
}