#include "graphics.h"
#include "engine.h"
#include "stdlib.h"

typedef struct
{
    int x;
    int y;
    int z;
}vec3int;

int geo_obj_loadFromFile(const char* filename, GeoObject *obj)
{
    printf("GEO: %s : Loading obj... ", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("FILE NOT FOUND\n");
        return 1;
    }

    vec3 *vBuffer = malloc(sizeof(vec3) * 128);
    int vBuffLen = 128;
    int vCount = 0;
    vec2 *vtBuffer = malloc(sizeof(vec2) * 128);
    int vtBuffLen = 128;
    int vtCount = 0;
    vec3 *vnBuffer = malloc(sizeof(vec3) * 128);
    int vnBuffLen = 128;
    int vnCount = 0;

    vec3int *vertexIndices = malloc(sizeof(vec3int) * 128);
    vec3int *uvIndices = malloc(sizeof(vec3int) * 128);
    vec3int *normalIndices = malloc(sizeof(vec3int) * 128);
    int iAlloc = 128;
    int iCount = 0;




    int fileEnded = 0;
    while ( !fileEnded )
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) fileEnded = 1;

        if (strcmp(lineHeader, "v") == 0)
        {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            if (vCount == vBuffLen)
            {
                printf("v: %d\n", vCount);
                vBuffer = realloc(vBuffer, sizeof(vec3) * (vBuffLen + 128));
                vBuffLen = vBuffLen + 128;
            }
            vBuffer[vCount].x = vertex.x;
            vBuffer[vCount].y = vertex.y;
            vBuffer[vCount].z = vertex.z;
            vCount = vCount + 1;
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            if (vtCount == vtBuffLen)
            {
                printf("vt: %d\n", vtCount);
                vtBuffer = realloc(vtBuffer, sizeof(vec2) * (vtBuffLen + 128));
                vtBuffLen = vtBuffLen + 128;
            }
            vtBuffer[vtCount].x = uv.x;
            vtBuffer[vtCount].y = uv.y;
            vtCount = vtCount + 1;
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            if (vnCount == vnBuffLen)
            {
                printf("vn: %d\n", vnCount);
                vnBuffer = realloc(vnBuffer, sizeof(vec3) * (vnBuffLen + 128));
                vnBuffLen = vnBuffLen + 128;
            }
            vnBuffer[vnCount].x = normal.x;
            vnBuffer[vnCount].y = normal.y;
            vnBuffer[vnCount].z = normal.z;
            vnCount = vnCount + 1;
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            
            if ((iCount + 1) == iAlloc)
            {
                printf("i: %d\n", iCount);
                vertexIndices = realloc(vertexIndices ,sizeof(vec3int) * (iAlloc + 128));
                uvIndices = realloc(uvIndices , sizeof(vec3int) * (iAlloc + 128));
                normalIndices = realloc(normalIndices ,sizeof(vec3int) * (iAlloc + 128));
                iAlloc = iAlloc + 128;
            }
            vertexIndices[iCount].x = vertexIndex[0];
            vertexIndices[iCount].y = vertexIndex[1];
            vertexIndices[iCount].z = vertexIndex[2];
            uvIndices[iCount].x = uvIndex[0];
            uvIndices[iCount].y = uvIndex[1];
            uvIndices[iCount].z = uvIndex[2];
            normalIndices[iCount].x = normalIndex[0];
            normalIndices[iCount].y = normalIndex[1];
            normalIndices[iCount].z = normalIndex[2];
            iCount = iCount + 1;
        }
    }

    

    int vertCount = (iCount - 1) * 3;

    obj->bufferLength = sizeof(vec3) * vertCount;
    obj->triCount = (iCount - 1);
    obj->vertexBuffer = malloc(sizeof(vec3) * vertCount);
    obj->uvBuffer = malloc(sizeof(vec2) * vertCount);

    int *vi = (int*)vertexIndices;
    int *ui = (int*)uvIndices;

    for (int i = 0; i < vertCount; i++)
    {
        int vertexIndex = vi[i];
        int uvIndex = ui[i];
        vec3 vertex = vBuffer[vertexIndex - 1];
        vec2 uv = vtBuffer[uvIndex - 1];
        obj->vertexBuffer[i] = vertex;
        obj->uvBuffer[i] = uv;
    }

    fclose(file);
    free(vBuffer);
    free(vtBuffer);
    free(vnBuffer);
    free(vertexIndices);
    free(uvIndices);
    free(normalIndices);

    printf("OK\n----------FILE STATS----------\n");
    printf("polygons to render: %d\n", iCount - 1);
    printf("polygons on disk: %d\n", vCount - 1);
    printf("verts to render: %d\n", vertCount);
    printf("verts on disk: %d\n------------------------------\n", (vCount - 1) * 3);

    return 0;
}