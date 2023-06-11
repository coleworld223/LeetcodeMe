//https://leetcode.com/contest/weekly-contest-349/problems/maximum-sum-queries/
class Solution {
public:
    using ll = int;
    using pll = pair <ll, pair <ll, ll>>;
    vector<int> maximumSumQueries(vector<int>& a, vector<int>& b, vector<vector<int>>& q) {
      int n = a.size();
      vector <pair <ll, ll>> V;
      for (int i = 0; i < n; i++) {
        pair <ll, ll> C = {a[i], b[i]};
        V.push_back(C);
      }
      vector <pair <ll, pair <ll, ll>>> q1(q.size());
      sort(V.begin(), V.end());
      for (ll i = 0; i < q.size(); i++) {
        q1[i] = {i, {q[i][0], q[i][1]}};
      }
      sort(q1.begin(), q1.end(),[&] (pll &a, pll &b){
        return a.second.first > b.second.first;
      });
      // for (auto val : q1) {
      //   cout << val.second.first << " " << val.second.second << endl;
      // }
      

      ll nq = q.size();
      ll at = n - 1;
      vector <ll> ans(nq);
      map <ll, ll> mp;
      for (ll i = 0; i < nq; i++) {
        ll x = q1[i].second.first;
        ll y = q1[i].second.second;
        ll lo = 0;
        ll hi = n - 1;
        while(hi - lo > 1) {
          ll mid = lo + (hi - lo) / 2;
          if(V[mid].first < x)lo = mid;
          else hi = mid;
        }
        ll idx = 0;
        if(V[lo].first >= x) {
          idx = lo;
        }
        else if(V[hi].first >= x) {
          idx = hi;
        }
        else{
          ans[q1[i].first] = -1;
          continue;
        }
        if(at >= idx) {
          while(at >= idx) {
            ll sum = V[at].first + V[at].second;
            ll b = V[at].second;
            if(mp.lower_bound(b) == mp.end()) {
              while(!mp.empty() && (*(--mp.end())).second <= sum) {
                mp.erase((--mp.end()));
              }
              mp[b] = sum;
            }
            else{
              if((*mp.lower_bound(b)).second <= sum) {
                mp[b] = sum;
              }
            }
            at--;
          }
        }
        auto it = mp.lower_bound(y);
        
        if(it == mp.end())ans[q1[i].first] = -1;
        else{
          ans[q1[i].first] = (*it).second;
        }
      }
      return ans;
    }
};
