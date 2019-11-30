List neighbors (Graph *G, int x) {	
	int y, e ;
	List list;
	make_null(&list);
	for (y = 1; y <= G->n; y++){
		if (x==y)
			continue;
		for (e = 1; e <= G->n; e++)	
			if (G->A[x][e] == 1 && G->A[y][e] == 1)
				push_back(&list, y);
	}	
	return list;
}
