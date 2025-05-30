-- Compute

#version 430

layout (local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

layout (std430, binding = 0) writeonly buffer OutputBuffer {
    uint outputBuffer[];
};

#define MEM_SIZE 4096
shared uint memBuf1[MEM_SIZE];
shared uint memBuf2[MEM_SIZE];

void main() {
    const uint iterations = MEM_SIZE / gl_WorkGroupSize.x;
    const uint localIdx = gl_LocalInvocationID.x * iterations;
    for (uint i = 0u, l = localIdx; i < iterations; i++, l++) {
        memBuf1[l] = 0x0u;
        memBuf2[l] = ~0x0u;
    }
    barrier();

    for (uint i = 0u, l = localIdx; i < iterations; i++, l++) {
        outputBuffer[l] = (memBuf1[l] << 16u) | (memBuf2[l] & 0xFFFFu);
    }
}
