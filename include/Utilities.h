#pragma once

#include<SDL2/SDL.h>
#include<bits/stdc++.h>
using namespace std;

double distance(int x1, int y1, int x2, int y2);

long long RandNum(long long l, long long r);

void paintBrush(SDL_Renderer* renderer, int x, int y, int radius);

void DrawSmoothStroke(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int radius);

void SetColor(SDL_Renderer* renderer, SDL_Color color);

bool detectRed(const vector<pair<int, int>> &points);

bool detectBlue(const vector<pair<int, int>> &points);

bool detectYellow(const vector<pair<int, int>> &points);

bool detectGreen(const vector<pair<int, int>> &points);

bool detectHeart(const vector<pair<int, int>> &points);
