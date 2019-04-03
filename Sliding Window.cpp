
/*
Topic: Finding min or max element of K consecutive elements
Problem: LightOJ 1093 - Ghajini, BOI'07 Sound
Caller functions:
    vector<int> mmin = sliding_window_minmax(arr, k, false); //num is the input array
    vector<int> mmax = sliding_window_minmax(arr, k, true); // d is the size of the window
*/
vector<int> sliding_window_minmax(vector<int> & ARR, int K, bool mx) { // K = window size; bool mx = true to find max; false to find min
    deque< pair<int, int> > window;
    vector<int> ans;
    for (int i = 0; i < ARR.size(); i++) {
        if (mx) {
            while (!window.empty() && window.back().first <= ARR[i]) window.pop_back();
        }
        else {
            while (!window.empty() && window.back().first >= ARR[i]) window.pop_back();
        }
        window.push_back(make_pair(ARR[i], i));
        while(window.front().second <= i - K) window.pop_front();
        ans.push_back(window.front().first);
    }
    return ans;
}
