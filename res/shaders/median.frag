#version 420 core

#ifndef KERNEL_HALF_SIZE_X
#define KERNEL_HALF_SIZE_X 0
#endif
#define KERNEL_SIZE_X (2 * (KERNEL_HALF_SIZE_X) + 1)

#ifndef KERNEL_HALF_SIZE_Y
#define KERNEL_HALF_SIZE_Y 0
#endif
#define KERNEL_SIZE_Y (2 * (KERNEL_HALF_SIZE_Y) + 1)

const ivec2 kernel_half_size = ivec2(KERNEL_HALF_SIZE_X, KERNEL_HALF_SIZE_Y);
const ivec2 kernel_size = ivec2(KERNEL_SIZE_X, KERNEL_SIZE_Y);

uniform sampler2D image;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;


vec4 colors[KERNEL_SIZE_X * KERNEL_SIZE_Y];
void swap(inout vec4 a, inout vec4 b) {
    vec4 t = a;
    a = b;
    b = t;
}

int quickPartition(int left, int right) {
    vec4 pivotValue = colors[right];
    int pivotIndex = left;

    for (int i = left; i < right; i++) {
        if (colors[i].a <= pivotValue.a) {
            swap(colors[i], colors[pivotIndex]);
            pivotIndex++;
        }
    }

    swap(colors[pivotIndex], colors[right]);
    return pivotIndex;
}

vec4 quickMedian() {
    int left = 0;
    int right = kernel_size.x * kernel_size.y - 1;
    int k = (right + left) / 2;

    int iter = 1;
    while (left <= right) {
        int index = quickPartition(left, right);

        if (index == k) {
            return colors[index];
        } else if (index < k) {
            left = index + 1;
        } else {
            right = index - 1;
        }
    }
    return colors[left];
}

float grayscale(vec3 color) {
    return dot(color, vec3(0.3, 0.59, 0.11) / 3);
}

void main() {
    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0);
    int index = 0;
    for (int dx = -kernel_half_size.x; dx < kernel_half_size.x; dx += 1) {
        for (int dy = -kernel_half_size.y; dy < kernel_half_size.y; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;
            vec3 color = texture2D(image, image_delta).rgb;

            colors[index] = vec4(color, grayscale(color));
            index++;
        }
    }

    vec4 median_color = quickMedian();
//    vec4 median_color = colors[0];
    gl_FragColor = vec4(median_color.rgb, 1.0);
}
