#ifndef GRAPHEDGE
#define GRAPHEDGE

class GraphEdge
{
public:
	GraphEdge(int start, int end);
	int getEdgeStart();
	int getEdgeEnd();

protected:
	int m_start;
	int m_end;
	const int weight = 1;
};
#endif
