void merge(const auto& v) {
    int L = v[0], R = v[1];
    auto it = mp.lower_bound(L);
    if(it!=mp.begin() && prev(it)->second>=L) it--;
    while(it!=mp.end() && it->first<=R) {
        L = min(L, it->first);
        R = max(R, it->second);
        it = mp.erase(it);
    }
    mp[L] = R;
}
