#version 420 core

uniform sampler2D image;
uniform sampler2D x_kernel;
uniform sampler2D y_kernel;

uniform bool return_direction;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

vec3 convolution(sampler2D image, sampler2D kernel) {
    ivec2 kernel_size =  textureSize(x_kernel, 0);
    ivec2 kernel_half_size = (x_kernel_size - ivec2(1)) / 2;
    vec2 kernel_texel_size = 1 / vec2(kernel_size.xy);

    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0);
    for (int dx = -kernel_half_size.x; dx < kernel_half_size.x; dx += 1) {
        for (int dy = -kernel_half_size.y; dy < kernel_size.y; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;
            vec2 kernel_delta = (ivec2(dx, dy) + kernel_half_size) * kernel_texel_size;

            color += texture2D(kernel, kernel_delta).r * texture2D(image, image_delta).rgb;
        }
    }
    return color;
}

void main() {
    vec3 x_color = convolution(image, x_kernel);
    vec3 y_color = convolution(image, y_kernel);

    if (return_direction) {
        vec3 magnitude = sqrt(pow(x_color, 2)+ pow(y_color, 2));
        gl_FragColor = vec4(clamp(magnitude, vec3(0), vec3(1)), 1);
    } else {
        vec3 direction = atan2(x_color, y_color);
        gl_FragColor = vec4(direction, 1);
    }
}
