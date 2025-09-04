constexpr int s_faceCount = 4;
constexpr int s_sideCount = 6;
constexpr int s_vertexCount = 8;
constexpr int s_edgeCount = 12;
constexpr int s_sideOrder[s_sideCount][s_faceCount] = {
	{ 0, 1, 2, 3, },
	{ 1, 4, 7, 2, },
	{ 4, 5, 6, 7, },
	{ 5, 0, 3, 6, },
	{ 3, 2, 7, 6, },
	{ 0, 5, 4, 1, },
};
constexpr int s_sideJumps[s_sideCount][s_faceCount] = {
	{ 5, 1, 4, 3, },
	{ 5, 2, 4, 0, },
	{ 5, 3, 4, 1, },
	{ 5, 0, 4, 2, },
	{ 0, 1, 2, 3, },
	{ 3, 2, 1, 0, },
};
constexpr int s_edgeLookup[s_vertexCount][s_vertexCount] = {
//     0   1   2   3   4   5   6   7
	{ -2, +0, -1, +3, -1, +4, -1, -1, }, // 0
	{ +0, -2, +1, -1, +5, -1, -1, -1, }, // 1
	{ -1, +1, -2, +2, -1, -1, -1, +6, }, // 2
	{ +3, -1, +2, -2, -1, -1, +7, -1, }, // 3
	{ -1, +5, -1, -1, -2, +8, -1, +9, }, // 4
	{ +4, -1, -1, -1, +8, -2, 11, -1, }, // 5
	{ -1, -1, -1, +7, -1, 11, -2, 10, }, // 6
	{ -1, -1, +6, -1, +9, -1, 10, -2, }, // 7
};

const int s_edges[s_edgeCount][2] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
	{ 0, 5 }, { 1, 4 }, { 2, 7 }, { 3, 6 },
	{ 4, 5 }, { 7, 4 }, { 6, 7 }, { 5, 6 },
};
const int s_edgeSides[s_edgeCount][2] = {
	{ 0, 5 }, { 0, 1 }, { 0, 4 }, { 0, 3 },
	{ 3, 5 }, { 5, 1 }, { 1, 4 }, { 4, 3 },
	{ 2, 5 }, { 2, 1 }, { 2, 4 }, { 2, 3 },
};



// const s_vertexPositions : Array[Vector3i] = [
// 	Vector3i(0, 0, 0),
// 	Vector3i(1, 0, 0),
// 	Vector3i(1, 1, 0),
// 	Vector3i(0, 1, 0),
// 	Vector3i(1, 0, 1),
// 	Vector3i(0, 0, 1),
// 	Vector3i(0, 1, 1),
// 	Vector3i(1, 1, 1),
// ];