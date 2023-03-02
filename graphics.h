#pragma once

//qx DrawCircle(double x1, double y1, double radius);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
enum viewtype {top_view, perspective_view, rat_view};
extern viewtype current_view;