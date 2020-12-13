#version 420 core

uniform sampler2D image;
uniform sampler2D kernel;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

void main() {
    gl_FragColor = texture2D(image, in_Data.texture_coordinate.xy);
}