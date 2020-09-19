#include "CubeDecoder.h"

static uint8_t converse_angle_set_single_x_first(uint8_t result[55], uint8_t face, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3) {
    uint8_t ret = 0;
    switch (face) {
        case 1:
            result[p1] = c3;
            result[p2] = c1;
            result[p3] = c2;
            break;
        case 2:
            result[p1] = c2;
            result[p2] = c3;
            result[p3] = c1;
            break;
        case 3:
            result[p1] = c1;
            result[p2] = c2;
            result[p3] = c3;
            break;
        default:
            ret = 1;
    }
    return ret;
}

static uint8_t converse_angle_set_single_y_first(uint8_t result[55], uint8_t face, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3) {
    uint8_t ret = 0;
    switch (face) {
        case 2:
            result[p1] = c3;
            result[p2] = c1;
            result[p3] = c2;
            break;
        case 1:
            result[p1] = c2;
            result[p2] = c3;
            result[p3] = c1;
            break;
        case 3:
            result[p1] = c1;
            result[p2] = c2;
            result[p3] = c3;
            break;
        default:
            ret = 1;
    }
    return ret;
}

static uint8_t converse_angle_x(uint8_t result[55], uint8_t angle, uint8_t face, uint8_t f1, uint8_t f2, uint8_t f3) {
    uint8_t num = 0;
    switch (angle) {
        case 1:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 1, 2, 3);
            break;
        case 2:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 1, 3, 4);
            break;
        case 3:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 1, 4, 5);
            break;
        case 4:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 1, 5, 2);
            break;
        case 5:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 6, 3, 2);
            break;
        case 6:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 6, 4, 3);
            break;
        case 7:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 6, 5, 4);
            break;
        case 8:
            num = num | converse_angle_set_single_x_first(result, face, f1, f2, f3, 6, 2, 5);
            break;
        default:
            num = num | 2;
    }

    return num;
}

static uint8_t converse_angle_y(uint8_t result[55], uint8_t angle, uint8_t face, uint8_t f1, uint8_t f2, uint8_t f3) {
    uint8_t num = 0;
    switch (angle) {
        case 1:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 1, 2, 3);
            break;
        case 2:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 1, 3, 4);
            break;
        case 3:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 1, 4, 5);
            break;
        case 4:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 1, 5, 2);
            break;
        case 5:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 6, 3, 2);
            break;
        case 6:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 6, 4, 3);
            break;
        case 7:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 6, 5, 4);
            break;
        case 8:
            num = num | converse_angle_set_single_y_first(result, face, f1, f2, f3, 6, 2, 5);
            break;
        default:
            num = num | 2;
    }

    return num;
}

static uint8_t converse_line_set_single(uint8_t result[55], uint8_t line_face, uint8_t p1, uint8_t p2, uint8_t c1, uint8_t c2) {
    uint8_t ret = 0;
    if (line_face == 1) {
        result[p1] = c1;
        result[p2] = c2;
    } else if (line_face == 2) {
        result[p1] = c2;
        result[p2] = c1;
    } else {
        ret = 3;
    }

    return ret;
}

static uint8_t converse_line_set(uint8_t result[55], uint8_t line, uint8_t line_face, uint8_t p1, uint8_t p2) {
    uint8_t num = 0;
    switch (line) {
        case 1:
            num = num | converse_line_set_single(result, line_face, p1, p2, 1, 2);
            break;
        case 2:
            num = num | converse_line_set_single(result, line_face, p1, p2, 1, 3);
            break;
        case 3:
            num = num | converse_line_set_single(result, line_face, p1, p2, 1, 4);
            break;
        case 4:
            num = num | converse_line_set_single(result, line_face, p1, p2, 1, 5);
            break;
        case 5:
            num = num | converse_line_set_single(result, line_face, p1, p2, 2, 3);
            break;
        case 6:
            num = num | converse_line_set_single(result, line_face, p1, p2, 4, 3);
            break;
        case 7:
            num = num | converse_line_set_single(result, line_face, p1, p2, 4, 5);
            break;
        case 8:
            num = num | converse_line_set_single(result, line_face, p1, p2, 2, 5);
            break;
        case 9:
            num = num | converse_line_set_single(result, line_face, p1, p2, 6, 2);
            break;
        case 10:
            num = num | converse_line_set_single(result, line_face, p1, p2, 6, 3);
            break;
        case 11:
            num = num | converse_line_set_single(result, line_face, p1, p2, 6, 4);
            break;
        case 12:
            num = num | converse_line_set_single(result, line_face, p1, p2, 6, 5);
            break;
        default:
            num = 4;
    }
    return num;
}

static void converse_change_face_again(uint8_t result[55], uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4) {
    uint8_t num = result[a4];
    result[a4] = result[a3];
    result[a3] = result[a2];
    result[a2] = result[a1];
    result[a1] = num;
}

static void converse_to_paper_type(uint8_t result[6][9], uint8_t decoded_cube_data[20]) {

    int num = 0;
    uint8_t result_buffer[55] = {0};
    uint8_t buf1[12];
    uint8_t buf2[12];
    uint8_t buf3[12];
    uint8_t buf4[12];

    // Set the middle pieces
    result_buffer[32] = 1;
    result_buffer[41] = 2;
    result_buffer[50] = 3;
    result_buffer[14] = 4;
    result_buffer[23] = 5;
    result_buffer[5] = 6;

    // Do stuff (copied, no idea what happes here)
    buf1[0] = decoded_cube_data[0] >> 4;
    buf1[1] = decoded_cube_data[0] & 15;
    buf1[2] = decoded_cube_data[1] >> 4;
    buf1[3] = decoded_cube_data[1] & 15;
    buf1[4] = decoded_cube_data[2] >> 4;
    buf1[5] = decoded_cube_data[2] & 15;
    buf1[6] = decoded_cube_data[3] >> 4;
    buf1[7] = decoded_cube_data[3] & 15;
    buf2[0] = decoded_cube_data[4] >> 4;
    buf2[1] = decoded_cube_data[4] & 15;
    buf2[2] = decoded_cube_data[5] >> 4;
    buf2[3] = decoded_cube_data[5] & 15;
    buf2[4] = decoded_cube_data[6] >> 4;
    buf2[5] = decoded_cube_data[6] & 15;
    buf2[6] = decoded_cube_data[7] >> 4;
    buf2[7] = decoded_cube_data[7] & 15;
    buf3[0] = decoded_cube_data[8] >> 4;
    buf3[1] = decoded_cube_data[8] & 15;
    buf3[2] = decoded_cube_data[9] >> 4;
    buf3[3] = decoded_cube_data[9] & 15;
    buf3[4] = decoded_cube_data[10] >> 4;
    buf3[5] = decoded_cube_data[10] & 15;
    buf3[6] = decoded_cube_data[11] >> 4;
    buf3[7] = decoded_cube_data[11] & 15;
    buf3[8] = decoded_cube_data[12] >> 4;
    buf3[9] = decoded_cube_data[12] & 15;
    buf3[10] = decoded_cube_data[13] >> 4;
    buf3[11] = decoded_cube_data[13] & 15;

    if ((decoded_cube_data[14] & 128) != 0) {
        buf4[0] = 2;
    } else {
        buf4[0] = 1;
    }
    if ((decoded_cube_data[14] & 64) != 0) {
        buf4[1] = 2;
    } else {
        buf4[1] = 1;
    }
    if ((decoded_cube_data[14] & 32) != 0) {
        buf4[2] = 2;
    } else {
        buf4[2] = 1;
    }
    if ((decoded_cube_data[14] & 16) != 0) {
        buf4[3] = 2;
    } else {
        buf4[3] = 1;
    }
    if ((decoded_cube_data[14] & 8) != 0) {
        buf4[4] = 2;
    } else {
        buf4[4] = 1;
    }
    if ((decoded_cube_data[14] & 4) != 0) {
        buf4[5] = 2;
    } else {
        buf4[5] = 1;
    }
    if ((decoded_cube_data[14] & 2) != 0) {
        buf4[6] = 2;
    } else {
        buf4[6] = 1;
    }
    if ((decoded_cube_data[14] & 1) != 0) {
        buf4[7] = 2;
    } else {
        buf4[7] = 1;
    }
    if ((decoded_cube_data[15] & 128) != 0) {
        buf4[8] = 2;
    } else {
        buf4[8] = 1;
    }
    if ((decoded_cube_data[15] & 64) != 0) {
        buf4[9] = 2;
    } else {
        buf4[9] = 1;
    }
    if ((decoded_cube_data[15] & 32) != 0) {
        buf4[10] = 2;
    } else {
        buf4[10] = 1;
    }
    if ((decoded_cube_data[15] & 16) != 0) {
        buf4[11] = 2;
    } else {
        buf4[11] = 1;
    }

    num = num | converse_angle_x(result_buffer, buf1[0], buf2[0], 34, 43, 54);
    num = num | converse_angle_y(result_buffer, buf1[1], buf2[1], 36, 52, 18);
    num = num | converse_angle_x(result_buffer, buf1[2], buf2[2], 30, 16, 27);
    num = num | converse_angle_y(result_buffer, buf1[3], buf2[3], 28, 25, 45);
    num = num | converse_angle_y(result_buffer, buf1[4], buf2[4], 1, 48, 37);
    num = num | converse_angle_x(result_buffer, buf1[5], buf2[5], 3, 12, 46);
    num = num | converse_angle_y(result_buffer, buf1[6], buf2[6], 9, 21, 10);
    num = num | converse_angle_x(result_buffer, buf1[7], buf2[7], 7, 39, 19);

    num = num | converse_line_set(result_buffer, buf3[0], buf4[0], 31, 44);
    num = num | converse_line_set(result_buffer, buf3[1], buf4[1], 35, 53);
    num = num | converse_line_set(result_buffer, buf3[2], buf4[2], 33, 17);
    num = num | converse_line_set(result_buffer, buf3[3], buf4[3], 29, 26);
    num = num | converse_line_set(result_buffer, buf3[4], buf4[4], 40, 51);
    num = num | converse_line_set(result_buffer, buf3[5], buf4[5], 15, 49);
    num = num | converse_line_set(result_buffer, buf3[6], buf4[6], 13, 24);
    num = num | converse_line_set(result_buffer, buf3[7], buf4[7], 42, 22);
    num = num | converse_line_set(result_buffer, buf3[8], buf4[8], 4, 38);
    num = num | converse_line_set(result_buffer, buf3[9], buf4[9], 2, 47);
    num = num | converse_line_set(result_buffer, buf3[10], buf4[10], 6, 11);
    num = num | converse_line_set(result_buffer, buf3[11], buf4[11], 8, 20);

    converse_change_face_again(result_buffer, 1, 7, 9, 3);
    converse_change_face_again(result_buffer, 4, 8, 6, 2);
    converse_change_face_again(result_buffer, 37, 19, 10, 46);
    converse_change_face_again(result_buffer, 38, 20, 11, 47);
    converse_change_face_again(result_buffer, 39, 21, 12, 48);
    converse_change_face_again(result_buffer, 40, 22, 13, 49);
    converse_change_face_again(result_buffer, 41, 23, 14, 50);
    converse_change_face_again(result_buffer, 42, 24, 15, 51);
    converse_change_face_again(result_buffer, 43, 25, 16, 52);
    converse_change_face_again(result_buffer, 44, 26, 17, 53);
    converse_change_face_again(result_buffer, 45, 27, 18, 54);
    converse_change_face_again(result_buffer, 34, 28, 30, 36);
    converse_change_face_again(result_buffer, 31, 29, 33, 35);

    // Skip the first entry and make it 2-dimesional
    for (uint8_t i=0; i < 6; i++) {
      for (uint8_t j=0; j < 9; j++) {
        if (num != 0) {
          result[i][j] = -1;
        } else {
          result[i][j] = result_buffer[i*9+j+1] - 1;
        }
      }
    }
}


static void cube_data_mix_decode(uint8_t result_buffer[20], uint8_t cube_data[20]) {

    uint8_t code_array[36] = {80, 175, 152, 32, 170, 119, 19, 137, 218, 230, 63, 95,
              46, 130, 106, 175, 163, 243, 20, 7, 167, 21, 168, 232,
              143, 175, 42, 125, 126, 57, 254, 87, 217, 91, 85, 215};

    uint8_t b = cube_data[19] & 15;
    uint8_t b2 = cube_data[19] >> 4;

    for (uint8_t i = 0; i < 19; i++) {
        result_buffer[i] = cube_data[i] - code_array[b+i] - code_array[b2+i];
    }
    result_buffer[19] = 0;
}


void parse_cube(uint8_t result_buffer[6][9], uint8_t cube_data[20]) {
    uint8_t mix_buffer[20];
    cube_data_mix_decode(mix_buffer, cube_data);
    converse_to_paper_type(result_buffer, mix_buffer);
}
