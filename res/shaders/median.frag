#version 420 core

#define USE_UNROLLED_SORT
#define MAX_KERNEL_HALF_SIZE 2
#define COMPARE_SWAP(i, j) \
 { if (colors[i].a < colors[j].a) { vec4 temp = colors[i]; colors[j] = colors[i]; colors[i] = temp; } }

uniform ivec2 kernel_half_size;
uniform sampler2D image;

in TVertexData {
    vec2 texture_coordinate;
} in_Data;

vec4 colors[(2 * MAX_KERNEL_HALF_SIZE + 1) * (2 * MAX_KERNEL_HALF_SIZE + 1)];

#ifdef USE_UNROLLED_SORT
void sort25() {
    // Generated with http://jgamble.ripco.net/cgi-bin/nw.cgi?inputs=25&algorithm=bosenelson&output=macro
    COMPARE_SWAP(0, 2); COMPARE_SWAP(0, 1); COMPARE_SWAP(1, 2); COMPARE_SWAP(4, 5); COMPARE_SWAP(3, 5); COMPARE_SWAP(3, 4); COMPARE_SWAP(0, 3); COMPARE_SWAP(1, 4); COMPARE_SWAP(2, 5); COMPARE_SWAP(2, 4); COMPARE_SWAP(1, 3); COMPARE_SWAP(2, 3); COMPARE_SWAP(7, 8); COMPARE_SWAP(6, 8); COMPARE_SWAP(6, 7); COMPARE_SWAP(10, 11); COMPARE_SWAP(9, 11); COMPARE_SWAP(9, 10); COMPARE_SWAP(6, 9); COMPARE_SWAP(7, 10); COMPARE_SWAP(8, 11); COMPARE_SWAP(8, 10);  COMPARE_SWAP(7, 9); COMPARE_SWAP(8, 9); COMPARE_SWAP(0, 6); COMPARE_SWAP(1, 7); COMPARE_SWAP(2, 8); COMPARE_SWAP(2, 7); COMPARE_SWAP(1, 6); COMPARE_SWAP(2, 6); COMPARE_SWAP(3, 9); COMPARE_SWAP(4, 10); COMPARE_SWAP(5, 11); COMPARE_SWAP(5, 10); COMPARE_SWAP(4, 9); COMPARE_SWAP(5, 9); COMPARE_SWAP(3, 6); COMPARE_SWAP(4, 7); COMPARE_SWAP(5, 8); COMPARE_SWAP(5, 7); COMPARE_SWAP(4, 6); COMPARE_SWAP(5, 6); COMPARE_SWAP(13, 14); COMPARE_SWAP(12, 14); COMPARE_SWAP(12, 13); COMPARE_SWAP(16, 17); COMPARE_SWAP(15, 17); COMPARE_SWAP(15, 16); COMPARE_SWAP(12, 15); COMPARE_SWAP(13, 16); COMPARE_SWAP(14, 17); COMPARE_SWAP(14, 16); COMPARE_SWAP(13, 15); COMPARE_SWAP(14, 15); COMPARE_SWAP(19, 20); COMPARE_SWAP(18, 20); COMPARE_SWAP(18, 19); COMPARE_SWAP(21, 22); COMPARE_SWAP(23, 24); COMPARE_SWAP(21, 23); COMPARE_SWAP(22, 24); COMPARE_SWAP(22, 23); COMPARE_SWAP(18, 22); COMPARE_SWAP(18, 21); COMPARE_SWAP(19, 23); COMPARE_SWAP(20, 24); COMPARE_SWAP(20, 23); COMPARE_SWAP(19, 21); COMPARE_SWAP(20, 22); COMPARE_SWAP(20, 21); COMPARE_SWAP(12, 19); COMPARE_SWAP(12, 18); COMPARE_SWAP(13, 20); COMPARE_SWAP(14, 21); COMPARE_SWAP(14, 20); COMPARE_SWAP(13, 18); COMPARE_SWAP(14, 19); COMPARE_SWAP(14, 18); COMPARE_SWAP(15, 22); COMPARE_SWAP(16, 23); COMPARE_SWAP(17, 24); COMPARE_SWAP(17, 23); COMPARE_SWAP(16, 22); COMPARE_SWAP(17, 22); COMPARE_SWAP(15, 19); COMPARE_SWAP(15, 18); COMPARE_SWAP(16, 20); COMPARE_SWAP(17, 21); COMPARE_SWAP(17, 20); COMPARE_SWAP(16, 18); COMPARE_SWAP(17, 19); COMPARE_SWAP(17, 18); COMPARE_SWAP(0, 13); COMPARE_SWAP(0, 12); COMPARE_SWAP(1, 14); COMPARE_SWAP(2, 15); COMPARE_SWAP(2, 14); COMPARE_SWAP(1, 12); COMPARE_SWAP(2, 13); COMPARE_SWAP(2, 12); COMPARE_SWAP(3, 16); COMPARE_SWAP(4, 17); COMPARE_SWAP(5, 18); COMPARE_SWAP(5, 17); COMPARE_SWAP(4, 16); COMPARE_SWAP(5, 16); COMPARE_SWAP(3, 13); COMPARE_SWAP(3, 12); COMPARE_SWAP(4, 14); COMPARE_SWAP(5, 15); COMPARE_SWAP(5, 14); COMPARE_SWAP(4, 12); COMPARE_SWAP(5, 13); COMPARE_SWAP(5, 12); COMPARE_SWAP(6, 19); COMPARE_SWAP(7, 20); COMPARE_SWAP(8, 21); COMPARE_SWAP(8, 20); COMPARE_SWAP(7, 19); COMPARE_SWAP(8, 19); COMPARE_SWAP(9, 22); COMPARE_SWAP(10, 23); COMPARE_SWAP(11, 24); COMPARE_SWAP(11, 23); COMPARE_SWAP(10, 22); COMPARE_SWAP(11, 22); COMPARE_SWAP(9, 19); COMPARE_SWAP(10, 20); COMPARE_SWAP(11, 21); COMPARE_SWAP(11, 20); COMPARE_SWAP(10, 19); COMPARE_SWAP(11, 19); COMPARE_SWAP(6, 13); COMPARE_SWAP(6, 12); COMPARE_SWAP(7, 14); COMPARE_SWAP(8, 15); COMPARE_SWAP(8, 14); COMPARE_SWAP(7, 12); COMPARE_SWAP(8, 13); COMPARE_SWAP(8, 12); COMPARE_SWAP(9, 16); COMPARE_SWAP(10, 17); COMPARE_SWAP(11, 18); COMPARE_SWAP(11, 17); COMPARE_SWAP(10, 16); COMPARE_SWAP(11, 16); COMPARE_SWAP(9, 13); COMPARE_SWAP(9, 12); COMPARE_SWAP(10, 14); COMPARE_SWAP(11, 15); COMPARE_SWAP(11, 14); COMPARE_SWAP(10, 12); COMPARE_SWAP(11, 13); COMPARE_SWAP(11, 12);
}
#else
vec4 leftArray[(2 * MAX_KERNEL_HALF_SIZE + 1) * (2 * MAX_KERNEL_HALF_SIZE + 1)];
void merge(int step, int a, int b, int c)
{
    int i;
    for (i = 0; i < step; ++i)
    leftArray[i] = colors[a+i];

    i = 0;
    int j = 0;
    for (int k = a; k < c; ++k)
    {
        if (b+j >= c || (i < step && leftArray[i].a > colors[b+j].a))
        colors[k] = leftArray[i++];
        else
        colors[k] = colors[b+j++];
    }
}
void sort25()
{
    int n = 25;
    int step = 1;
    while (step <= n)
    {
        int i = 0;
        while (i < n - step)
        {
            merge(step, i, i + step, min(i + step + step, n));
            i += 2 * step;
        }
        step *= 2;
    }
}
#endif

vec4 quickMedian(int size) {
    int left = 0;
    int right = size - 1;
    int k = (right + left) / 2;

    sort25();

    return colors[k];
}

float grayscale(vec3 color) {
    return dot(color, vec3(0.3, 0.59, 0.11) / 3);
}

void main() {
    const ivec2 kernel_size = kernel_half_size * 2 + 1;
    ivec2 image_size = textureSize(image, 0);
    vec2 image_texel_size = 1 / vec2(image_size.xy);

    vec3 color = vec3(0);
    int index = 0;
    for (int dx = -kernel_half_size.x; dx <= kernel_half_size.x; dx += 1) {
        for (int dy = -kernel_half_size.y; dy <= kernel_half_size.y; dy += 1) {
            vec2 image_delta = in_Data.texture_coordinate + vec2(dx, dy) * image_texel_size;
            vec3 color = texture2D(image, image_delta).rgb;

            colors[index] = vec4(color, grayscale(color));
            index++;
        }
    }

    vec4 median_color = quickMedian(kernel_size.x * kernel_size.y);
    gl_FragColor = vec4(median_color.rgb, 1.0);
}
