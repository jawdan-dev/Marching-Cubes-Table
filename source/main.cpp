#include <cstdio>
#include <vector>
#include <cstring>

#include "data.hpp"

// FORMAT:
// { edgeCount, e1, e2, ..., eN, edgeCount, e1, ..., eN, -1 };
constexpr int s_tableSize = 256;
std::vector<int> s_table[s_tableSize];

static bool s_vertices[8];
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(*arr))

bool s_traversed[s_edgeCount];
void traverse(const int entryIndex) {
	for (int i = 0; i < s_edgeCount; i++)
		s_traversed[i] = false;

	std::vector<int> edgeBuffer;

	for (int startEdge = 0; startEdge < s_edgeCount; startEdge++) {
		const int ev0 = s_edges[startEdge][0], ev1 = s_edges[startEdge][1];
		if (s_traversed[startEdge] || s_vertices[ev0] == s_vertices[ev1])
			continue;

		int sideIndex = s_vertices[ev0] ? s_edgeSides[startEdge][0] : s_edgeSides[startEdge][1],
			start = s_vertices[ev0] ? ev0 : ev1,
			next = s_vertices[ev0] ? ev1 : ev0;

		int faceOffset = 0;
		for (int i = 0; i < s_faceCount; i++) {
			if (s_sideOrder[sideIndex][i] != start)
				continue;
			faceOffset = i;
			break;
		}

		bool traversalFinished = false;
		while (!traversalFinished) {
			traversalFinished = true;
			for (int face = 0; face < s_faceCount; face++) {
				const int
					vFromIndex = (faceOffset + face) % s_faceCount,
					vToIndex = (faceOffset + face + 1) % s_faceCount,
					vFrom = s_sideOrder[sideIndex][vFromIndex],
					vTo = s_sideOrder[sideIndex][vToIndex],
					edgeIndex = s_edgeLookup[vFrom][vTo];

				if (s_traversed[edgeIndex])
					break;
				if (s_vertices[vTo])
					continue;
				s_traversed[edgeIndex] = true;

				edgeBuffer.emplace_back(edgeIndex);

				sideIndex = s_sideJumps[sideIndex][vFromIndex];
				for (int newFace = 0; newFace < s_faceCount; newFace++) {
					if (s_sideOrder[sideIndex][newFace] != vFrom)
						continue;
					faceOffset = newFace;
					break;
				}

				traversalFinished = false;
				break;
			}
		}
		s_table[entryIndex].emplace_back(edgeBuffer.size());
		for (int i = 0; i < edgeBuffer.size(); i++)
			s_table[entryIndex].emplace_back(edgeBuffer[i]);
		edgeBuffer.clear();
	}
	s_table[entryIndex].emplace_back(-1);
}

FILE* s_fileOut = nullptr;
template<typename ...T>
void writeToFile(const char* format, T ...args) {
	printf(format, args...);

	if (s_fileOut == nullptr) return;

	static char buffer[256];
	snprintf(buffer, sizeof(buffer) / sizeof(*buffer), format, args...);
	buffer[(sizeof(buffer) / sizeof(*buffer)) - 1] = '\0';

	fwrite(buffer, sizeof(*buffer), strlen(buffer), s_fileOut);
}


int main() {
	printf("\nOne Time,,, Two Time,,,\n");

	s_fileOut = fopen("out.gd", "wb");

	writeToFile("const s_edgeLookup = [\n");
	for (int n = 0; n < s_tableSize; n++) {
		for (int i = 0; i < ARRAY_LENGTH(s_vertices); i++)
			s_vertices[i] = (n >> i) & 0b1;

		traverse(n);

		writeToFile("    [ ");
		for (int i = 0; i < s_table[n].size(); i++)
			writeToFile("%i, ", s_table[n][i]);
		writeToFile("], \n");
	}
	writeToFile("];\n");
}
