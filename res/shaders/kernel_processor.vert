#version 420 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coordinate;

out TVertexData {
    vec2 texture_coordinate;
} out_Data;

void main() {
    gl_Position = vec4(position.xy, 0.0, 1.0);
    out_Data.texture_coordinate = texture_coordinate;
}
