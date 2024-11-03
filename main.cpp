#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using Node = tuple<ll, ll, ll, ll>;

ll K, W, H;
vvl M;
vvvl MK;

vl ndx{-1, 1, -2, 2, -2, 2, -1, 1};
vl ndy{-2, -2, -1, -1, 1, 1, 2, 2};
vl dx{-1, 1, 0, 0};
vl dy{0, 0, -1, 1};

ll solve() {
  queue<Node> Q{};
  Q.push({0, 0, 0, K});
  MK[K][0][0] = 1;

  while (!Q.empty()) {
    auto [fy, fx, t, k] = Q.front();
    Q.pop();

    if (fy == H - 1 && fx == W - 1) return t;

    if (k > 0) {
      for (auto d = 0; d < 8; ++d) {
        const auto& ny = fy + ndy[d];
        const auto& nx = fx + ndx[d];

        if (ny < 0 || H <= ny || nx < 0 || W <= nx) continue;
        if (MK[k - 1][ny][nx] == 1) continue;

        Q.push({ny, nx, t + 1, k - 1});
        MK[k - 1][ny][nx] = 1;
      }
    }

    for (auto d = 0; d < 4; ++d) {
      const auto& ny = fy + dy[d];
      const auto& nx = fx + dx[d];

      if (ny < 0 || H <= ny || nx < 0 || W <= nx) continue;
      if (MK[k][ny][nx] == 1) continue;

      Q.push({ny, nx, t + 1, k});
      MK[k][ny][nx] = 1;
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> K >> W >> H;
  M = vvl(H, vl(W));
  for (auto&& r : M) {
    for (auto&& m : r) cin >> m;
  }

  MK = vvvl(K + 1, M);

  const auto& ans = solve();
  cout << ans;

  return 0;
}