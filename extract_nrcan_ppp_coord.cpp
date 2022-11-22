// test_rtcm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

static void extract_coordinate(const char* fname)
{
    FILE* fLOG = fopen(fname, "rt");

    if (fLOG ==NULL) return;

    char buffer[255] = { 0 };

    double xyz[3] = { 0 };
    double rms_xyz[3] = { 0 };
    int idx[3] = { 0 };
    while (fLOG && !feof(fLOG))
    {
        fgets(buffer, sizeof(buffer), fLOG);
        if (strstr(buffer, "POS   X") && strlen(buffer) >= 84)
        {
            xyz[0] = atof(buffer + 44);
            rms_xyz[0] = atof(buffer + 73);
            idx[0]++;
        }
        if (strstr(buffer, "POS   Y") && strlen(buffer) >= 84)
        {
            xyz[1] = atof(buffer + 44);
            rms_xyz[1] = atof(buffer + 73);
            idx[1]++;
        }
        if (strstr(buffer, "POS   Z") && strlen(buffer) >= 84)
        {
            xyz[2] = atof(buffer + 44);
            rms_xyz[2] = atof(buffer + 73);
            idx[2]++;
        }
        if (idx[0] && idx[1] && idx[2])
        {
            printf("%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%s\n", xyz[0], xyz[1], xyz[2], rms_xyz[0], rms_xyz[1], rms_xyz[2], fname);
            break;
        }
    }
    if (fLOG) fclose(fLOG);
    return;
}

int main(int argc, const char* argv[])
{
    if (argc>1)
        extract_coordinate(argv[1]);
    return 0;
}

