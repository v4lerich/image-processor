#version 420 core

uniform sampler2D image;
uniform sampler2D kernel;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

void main() {
    ivec2 kernel_size =  textureSize(kernel, 0);
    ivec2 kernel_half = (kernel_size - ivec2(1, 1)) / 2;
    vec2 kernel_texel_size = 1 / vec2(kernel_size.xy);

    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0, 0, 0);
    for (int dx = -kernel_half.x; dx < kernel_half.x; dx += 1) {
        for (int dy = -kernel_half.y; dy < kernel_size.y; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;
            vec2 kernel_delta = (ivec2(dx, dy) + kernel_half) * kernel_texel_size;

            color += texture2D(kernel, kernel_delta).r * texture2D(image, image_delta).rgb;
        }
    }
    gl_FragColor = vec4(color.rgb, 1.0);
}