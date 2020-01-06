// Also updates [page_back].
void graph_showpage_func(page_t page);

void graph_accesspage_func(int page);
#undef graph_accesspage
#define graph_accesspage graph_accesspage_func
