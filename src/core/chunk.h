#ifndef CHUNK_H
#define CHUNK_H
#include "particles/particle.h"
#include "sim_matrix.h"

namespace powder_sim  {
	class SimMatrix;

	class Chunk
	{
	public:
		Chunk(int x, int y, int size, SimMatrix* matrix);

		void WakeUp();
		void Update();
		[[nodiscard]] bool IsSleeping() const;
		[[nodiscard]] int GetSize() const;

	private:
		bool is_sleeping_next_frame_;
		bool is_sleeping_;
		int size_;
		int offset_x_, offset_y_;
		SimMatrix* matrix_;
	};
}


#endif // CHUNK_H
