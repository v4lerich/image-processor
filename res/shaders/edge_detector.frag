#version 420 core

uniform sampler2D image;
uniform sampler2D x_kernel;
uniform sampler2D y_kernel;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

vec3 convolution(sampler2D image, sampler2D kernel) {
    ivec2 kernel_size =  textureSize(kernel, 0);
    ivec2 kernel_half_size = (kernel_size - ivec2(1, 1)) / 2;
    vec2 kernel_texel_size = 1 / vec2(kernel_size.xy);

    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0);
    for (int dx = -kernel_half_size.x; dx <= kernel_half_size.x; dx += 1) {
        for (int dy = -kernel_half_size.x; dy <= kernel_half_size.x; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;
            vec2 kernel_delta = (ivec2(dx, dy) + kernel_half_size) * kernel_texel_size + kernel_texel_size / 2;

            color += texture2D(kernel, kernel_delta).r * texture2D(image, image_delta).rgb;
        }
    }
    return color;
}

float grayscale(vec3 color) {
    return dot(color, vec3(0.3, 0.59, 0.11) / 3);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec3 x_color = clamp(convolution(image, x_kernel), vec3(0), vec3(1));
    vec3 y_color = clamp(convolution(image, y_kernel), vec3(0), vec3(1));

    vec3 magnitude =  sqrt(x_color * x_color + y_color * y_color);
    gl_FragColor = vec4(magnitude, 1);
}
