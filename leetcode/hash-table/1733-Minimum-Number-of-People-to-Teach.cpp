class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages,
                         vector<vector<int>>& friendships) {

        int m = languages.size();

        // Store the languages known by each user
        vector<vector<bool>> knows(m + 1, vector<bool>(n + 1, false));

        for (int i = 1; i <= m; i++) {
            for (int lang : languages[i - 1]) {
                knows[i][lang] = true;
            }
        }

        // Find users who cannot communicate with their friends
        vector<bool> needTeach(m + 1, false);

        for (auto &f : friendships) {
            int u = f[0];
            int v = f[1];

            bool common = false;

            for (int lang = 1; lang <= n; lang++) {
                if (knows[u][lang] && knows[v][lang]) {
                    common = true;
                    break;
                }
            }

            if (!common) {
                needTeach[u] = true;
                needTeach[v] = true;
            }
        }

        // Try teaching each language
        int ans = INT_MAX;

        for (int lang = 1; lang <= n; lang++) {
            int count = 0;

            for (int i = 1; i <= m; i++) {
                if (needTeach[i] && !knows[i][lang]) {
                    count++;
                }
            }

            ans = min(ans, count);
        }

        return ans;
    }
};