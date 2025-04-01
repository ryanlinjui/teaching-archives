#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1000
#define TAS_HEADER \
    "version 3\n" \
    "emuVersion 22020\n" \
    "palFlag 0\n" \
    "romFilename SuperMarioBros\n" \
    "romChecksum base64:jjYwGG411HcjG/j9UOVM3Q==\n" \
    "fourscore 0\n" \
    "microphone 0\n" \
    "port0 1\n" \
    "port1 0\n" \
    "port2 0\n" \
    "FDS 0\n" \
    "NewPPU 0\n" \
    "comment TA\n"

#define BUTTON_LIST "RLDUTSBA"
#define BUTTON_BASE_SET "|0|........|||"

#define SUBTITLE_MAX_LEN 200
#define SUBTITLE_BASE_SET "subtitle %ld %s"

void button_set_frame(char ***src, size_t *size, const char *button, const uint64_t start_frame, const uint64_t end_frame, const bool unset)
{
    // get button start frame from src
    uint64_t start = 0;
    for (int i = 0; i < *size; i++)
    {
        if((*src)[i][0] != '|') 
        {
            start = i;
            break;
        }
    }

    // end frame overflow issue, realloc src
    if(end_frame > ((*size) - start))
    {
        if(unset) return;
        for (int j = *size; j <= end_frame; j++)
        {
            *src = (char**)realloc(*src, (j+1) * sizeof(char**));
            (*src)[j] = (char*)calloc(strlen(BUTTON_BASE_SET)+1, sizeof(char*));
            strncpy((*src)[j], BUTTON_BASE_SET, strlen(BUTTON_BASE_SET));
        }
        *size = end_frame + 1;
    }
    
    // set/unset button to src
    for (int i = start; i < *size; i++)
    {
        if(i >= start_frame && i <= end_frame)
        {
            for (int b1 = 0; b1 < strlen(button); b1++)
            {
                for (int b2 = 0; b2 < strlen(BUTTON_LIST); b2++)
                {
                    if(BUTTON_LIST[b2] == button[b1])
                    {
                        if (!unset) (*src)[i][b2+3] = BUTTON_LIST[b2];
                        else (*src)[i][b2+3] = '.';
                        break;
                    }
                }                    
            }
        }
    }
}

void button_set_second(char ***src, size_t *size, const char *button, const double start_sec, const double end_sec, const bool unset)
{
    button_set_frame(src, size, button, (uint64_t)(start_sec * 60.0) - 1, (uint64_t)(end_sec * 60.0) - 1, unset);   
}

void subtitle_set_frame(char ***src, size_t *size, const char *subtitle, const uint64_t frame)
{
    // append src row size
    (*size)++;
    *src = (char**)realloc(*src, *size * sizeof(char**));
    (*src)[(*size) - 1] = (char*)calloc(1, sizeof(char*));

    // get button start frame from src
    uint64_t start = 0;
    for (int i = 0; i < *size; i++)
    {
        if((*src)[i][0] == '|') 
        {
            start = i;
            break;
        }
    }

    // src row move to next row
    for (int i = (*size)-1; i > start; i--)
    {
        free((*src)[i]);
        (*src)[i] = (char*)calloc((strlen((*src)[i-1]) + 1), sizeof(char*));
        memcpy((*src)[i], (*src)[i-1], strlen((*src)[i-1])* sizeof(char*));
    }
    
    // set subtitle
    (*src)[start] = (char*)realloc((*src)[start], (SUBTITLE_MAX_LEN + 1) * sizeof(char*));
    snprintf((*src)[start], SUBTITLE_MAX_LEN, SUBTITLE_BASE_SET, frame, subtitle);
}

void subtitle_set_second(char ***src, size_t *size, const char *subtitle, const double second)
{
    subtitle_set_frame(src, size, subtitle, (uint64_t)(second * 60.0) - 1);
}

void tas_read(char*** src, size_t *size)
{
    for (int i = 0; i < *size; i++)
    {
        if ((*src)[i]) free((*src)[i]);
    }
    if (*src) free(*src);
    *size = 0;
    *src = NULL;

    char *buffer = (char*)calloc(MAX_LEN, sizeof(char*));
    while (scanf("%[^\n]%*c", buffer) != -1)
    {
        *src = (char**)realloc(*src, ((*size)+1) * sizeof(char**));
        (*src)[*size] = (char*)calloc(strlen(buffer)+1, sizeof(char*));
        strncpy((*src)[*size], buffer, strlen(buffer));
        memset(buffer, 0, MAX_LEN);
        (*size)++;
    }
}

void tas_save(const char** src, const size_t size)
{
    if(!src) return;
    printf(TAS_HEADER);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", src[i]);
    }
}

void demo(char ***src, size_t *size)
{    
    for (int i = 0; i < *size; i++)
    {
        if ((*src)[i]) free((*src)[i]);
    }
    if (*src) free(*src);
    *size = 0;
    *src = NULL;

    button_set_second(src, size, "T", 3, 3, 0);
    subtitle_set_second(src, size, "press T", 3);
    
    button_set_second(src, size, "BR", 6, 30, 0);
    subtitle_set_second(src, size, "press B R", 6);
    
    button_set_frame(src, size, "A", 470, 500, 0);
    subtitle_set_frame(src, size, "press A from 470", 470);

    button_set_frame(src, size, "A", 515, 515, 0);
    subtitle_set_frame(src, size, "press A from 515", 515);

    button_set_frame(src, size, "A", 555, 590, 0);
    subtitle_set_frame(src, size, "press A from 555", 555);

    button_set_frame(src, size, "A", 610, 640, 0);
    subtitle_set_frame(src, size, "press A from 610", 610);

    button_set_frame(src, size, "A", 675, 710, 0);
    subtitle_set_frame(src, size, "press A from 670", 675);

    button_set_frame(src, size, "D", 740, 750, 0);
    button_set_frame(src, size, "BR", 710, 850, 1);
    subtitle_set_frame(src, size, "press D from 740, unset B, R from 710 to 900", 710);

    button_set_frame(src, size, "BRA", 880, 910, 0);
    subtitle_set_frame(src, size, "press B R A from 880", 910);

    button_set_frame(src, size, "A", 950, 950, 0);
    subtitle_set_frame(src, size, "press A from 950", 950);

    button_set_frame(src, size, "BRA", 1260, 1320, 0);
    subtitle_set_frame(src, size, "press B R A from 1260", 1260);

    button_set_frame(src, size, "A", 1260, 1280, 1);
    subtitle_set_frame(src, size, "unset A from 1260", 1260);

    button_set_frame(src, size, "BRA", 1350, 1390, 0);
    subtitle_set_frame(src, size, "press B R A from 1350", 1350);

    subtitle_set_frame(src, size, "contiued to press A from 1330", 1380);
    for (int i = 0; i < 30; i++)
    {
        button_set_frame(src, size, "BRA", 1400 + i*10, 1400 + i*10 + 5, 0);
    }

    subtitle_set_second(src, size, "finish 1-1 map by TA", 26.924);
}