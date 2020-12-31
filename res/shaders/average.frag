#version 420 core

uniform sampler2D image;
uniform ivec2 kernel_half_size;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

void main() {
    ivec2 kernel_size = 2 * kernel_half_size + 1;

    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0);
    for (int dx = -kernel_half_size.x; dx <= kernel_half_size.x; dx += 1) {
        for (int dy = -kernel_half_size.y; dy <= kernel_half_size.y; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;

            color += texture2D(image, image_delta).rgb;
        }
    }
    gl_FragColor = vec4(color / (kernel_size.x * kernel_size.y), 1);
}
