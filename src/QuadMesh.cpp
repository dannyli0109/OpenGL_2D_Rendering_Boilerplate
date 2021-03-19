#include "QuadMesh.h"


QuadMesh::QuadMesh()
{
	std::vector<FrameBufferVertex> vertices = {
		{ {-0.5f, 0.5f, 0 }, {0, 0} },
		{ {0.5f, 0.5f, 0 }, {1, 0} },
		{ {-0.5f, -0.5f, 0 }, {0, 1} },
		{ {0.5f, -0.5f, 0 }, {1, 1} }
	};

	//These are our indices - every three indices is a triangle, and refers to a position (a row of numbers) in the above vert array.
	std::vector<unsigned short> indices = {
		0, 1, 2, 1, 3, 2
	};

	CreateMesh(
		vertices.size(), sizeof(FrameBufferVertex), vertices.data(), {
			{3, GL_FLOAT, sizeof(FrameBufferVertex), (const void*)offsetof(FrameBufferVertex, FrameBufferVertex::position)},
			{2, GL_FLOAT, sizeof(FrameBufferVertex), (const void*)offsetof(FrameBufferVertex, FrameBufferVertex::uvs)}
		}, indices.size(), indices.data()
	);
}
