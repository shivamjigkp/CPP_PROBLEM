#include <bits/stdc++.h>
using namespace std;

struct Slide {
    int x1, y1, x2, y2;
    bool operator<(const Slide &other) const {
        if (x1 != other.x1) return x1 < other.x1;
        return y1 < other.y1;
    }
};

int main() {
    int N;
    cin >> N;
    vector<Slide> slides(N);
    for (int i = 0; i < N; i++) {
        cin >> slides[i].x1 >> slides[i].y1 >> slides[i].x2 >> slides[i].y2;
        // ensure x1 < x2 for consistency
        if (slides[i].x1 > slides[i].x2) swap(slides[i].x1, slides[i].x2), swap(slides[i].y1, slides[i].y2);
    }

    int x, y, energy;
    cin >> x >> y >> energy;

    // Simulation loop
    while (energy > 0 && y > 0) {
        // 1️⃣ Find the slide directly below (same x)
        Slide *hit = nullptr;
        int newY = -1;

        for (auto &s : slides) {
            // vertical drop intersects slide?
            if (s.x1 <= x && x <= s.x2) {
                // equation of line y = m*x + c
                double m = (double)(s.y2 - s.y1) / (s.x2 - s.x1);
                double c = s.y1 - m * s.x1;
                double yAtX = m * x + c;
                if (yAtX < y && yAtX > newY) { // below current y but highest possible
                    newY = (int)round(yAtX);
                    hit = &s;
                }
            }
        }

        if (!hit) { // no slide below → fall to ground
            y = 0;
            break;
        }

        // 2️⃣ Fall vertically onto slide
        y = newY;

        // 3️⃣ Slide along the slide
        int dx = (hit->x2 > hit->x1) ? 1 : -1;
        int dy = (hit->y2 > hit->y1) ? 1 : -1;

        while (energy > 0) {
            x += dx;
            y += dy;
            energy--;
            // stop if reached end of slide
            if ((dx > 0 && x > hit->x2) || (dx < 0 && x < hit->x1)) break;

            // check if stuck between slides (corner meeting)
            int touchCount = 0;
            for (auto &s : slides) {
                if (min(s.x1, s.x2) <= x && x <= max(s.x1, s.x2) &&
                    min(s.y1, s.y2) <= y && y <= max(s.y1, s.y2)) {
                    double m = (double)(s.y2 - s.y1) / (s.x2 - s.x1);
                    double c = s.y1 - m * s.x1;
                    double yy = m * x + c;
                    if (abs(yy - y) < 1e-6) touchCount++;
                }
            }

            if (touchCount > 1) { // stuck point
                int cost = x * y;
                if (energy >= cost) {
                    energy -= cost;
                } else {
                    energy = 0;
                    break;
                }
            }
        }
    }

    cout << x << " " << y << "\n";
    return 0;
}
