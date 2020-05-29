/*
 * Sasinosoft Map Loader
 * Copyright (c) 2017-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */

// Map Loader
#if defined _Sasinosoft_MapLoader_included
    #endinput
#endif
#define _Sasinosoft_MapLoader_included

#if !defined STRLIB_INC
#error This library depends on 'strlib'. Please include it before this library.
#endif

#if !defined _INC_SSCANF
#error This library depends on 'sscanf2'. Please include it before this library.
#endif

#define MapLoader. ML_

//
#define cell _
#define void _

//
#define MAPLDR_AUTO_CLEAR // comment if you do not want to automatically clear the cache at each Load() call

// Item limits per file 
#define MAPLDR_MAX_OBJECTS                       2048
#define MAPLDR_MAX_VEHICLES                      512
#define MAPLDR_MAX_REMOVALS                      1024
#define MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE       10
#define MAPLDR_MAX_MATERIALS_PER_OBJECT          10
#define MAPLDR_MAX_MATERIALS_PER_ATTACHMENT      10
#define MAPLDR_MAX_MATERIAL_TEXTS_PER_OBJECT     10
#define MAPLDR_MAX_MATERIAL_TEXTS_PER_ATTACHMENT 10
#define MAPLDR_MAX_CONSTANTS                     64

// Total limits
#define MAPLDR_TOTAL_MAX_REMOVALS 4096

// Length limits
#define MAPLDR_MAX_LINE_LENGTH                   256
#define MAPLDR_MAX_TXD_NAME_LENGTH               32
#define MAPLDR_MAX_TEXTURE_NAME_LENGTH           32
#define MAPLDR_MAX_MATERIAL_TEXT_LENGTH          32
#define MAPLDR_MAX_MATERIAL_TEXT_FONT_LENGTH     32
#define MAPLDR_MAX_CONSTANT_KEY_LENGTH           32
#define MAPLDR_MAX_CONSTANT_VALUE_LENGTH         128

// Messages
#define MAPLDR_FORMAT_ERROR    "Sasinosoft Map Loader | %s (%d) | data format error"
#define MAPLDR_LIMIT_ERROR     "Sasinosoft Map Loader | %s (%d) | %s limit has been reached"
#define MAPLDR_DIRECTIVE_ERROR "Sasinosoft Map Loader | %s (%d) | unknown directive \"%c\""
#define MAPLDR_NO_OBJ_ERROR    "Sasinosoft Map Loader | %s (%d) | object or vehicle was not specified"
#define MAPLDR_ERRORS          "Sasinosoft Map Loader | %s | %d errors"
#define MAPLDR_FILE_ERROR      "Sasinosoft Map Loader | %s | fatal error: cannot open input file"

// Default values
#define MAPLDR_DEFAULT_VW         -1 // default object virtual world
#define MAPLDR_DEFAULT_INT        -1 // default object interior
#define MAPLDR_DEFAULT_SD         100.0 // default object draw distance
#define MAPLDR_DEFAULT_DD         100.0 // default object stream distance
#define MAPLDR_DEFAULT_COL1       -1 // default vehicle color 1
#define MAPLDR_DEFAULT_COL2       -1 // default vehicle color 2
#define MAPLDR_DEFAULT_RESPAWN    -1 // default vehicle respawn delay
#define MAPLDR_DEFAULT_ADDSIREN   0 // default vehicle add siren
#define MAPLDR_DEFAULT_SIZE       90  // default material text size
#define MAPLDR_DEFAULT_FONT       "Arial"  // default material text font
#define MAPLDR_DEFAULT_FONT_SIZE  24  // default material text font size
#define MAPLDR_DEFAULT_BOLD       1  // default material text bold mode
#define MAPLDR_DEFAULT_FOREGROUND 0xFFFFFFFF  // default material text foreground color
#define MAPLDR_DEFAULT_BACKGROUND 0x00000000  // default material text background color
#define MAPLDR_DEFAULT_ALIGNMENT  0  // default material text alignment

//
#define MapLoaderObjectData. MLOD_
enum MapLoaderObjectData
{
    cell:  MapLoaderObjectData.Model,
    Float: MapLoaderObjectData.Position[3],
    Float: MapLoaderObjectData.Rotation[3],
    // Optional:
    cell:  MapLoaderObjectData.World,
    cell:  MapLoaderObjectData.Interior,
    Float: MapLoaderObjectData.StreamDistance,
    Float: MapLoaderObjectData.DrawDistance
}

//
#define MapLoaderVehicleData. MLVD_
enum MapLoaderVehicleData
{
    cell:  MapLoaderVehicleData.Model,
    Float: MapLoaderVehicleData.Position[3],
    Float: MapLoaderVehicleData.Rotation,
    // Optional: 
    cell:  MapLoaderVehicleData.Color[2],
    cell:  MapLoaderVehicleData.Respawn,
    cell:  MapLoaderVehicleData.AddSiren,
}

//
#define MapLoaderRemovalData. MLRD_
enum MapLoaderRemovalData
{
    cell:  MapLoaderRemovalData.Model,
    Float: MapLoaderRemovalData.Position[3],
    // Optional:
    Float: MapLoaderRemovalData.Radius
}

//
#define MapLoaderAttachmentData. MLAD_
enum MapLoaderAttachmentData
{
    cell:  MapLoaderAttachmentData.Model,
    Float: MapLoaderAttachmentData.Offset[3],
    Float: MapLoaderAttachmentData.Rotation[3],
    // Optional:
    cell:  MapLoaderAttachmentData.World,
    cell:  MapLoaderAttachmentData.Interior,
    Float: MapLoaderAttachmentData.StreamDistance,
    Float: MapLoaderAttachmentData.DrawDistance
}

//
#define MapLoaderMaterialData. MLMD_
enum MapLoaderMaterialData
{
    cell: MapLoaderMaterialData.Index,
    cell: MapLoaderMaterialData.Model,
    cell: MapLoaderMaterialData.Txd[MAPLDR_MAX_TXD_NAME_LENGTH],
    cell: MapLoaderMaterialData.Texture[MAPLDR_MAX_TEXTURE_NAME_LENGTH],
    cell: MapLoaderMaterialData.Color
}

//
#define MapLoaderMaterialTextData. MLMTD_
enum MapLoaderMaterialTextData
{
    cell: MapLoaderMaterialTextData.Index, 
    cell: MapLoaderMaterialTextData.Text[MAPLDR_MAX_MATERIAL_TEXT_LENGTH], 
    // Optional
    cell: MapLoaderMaterialTextData.Size, 
    cell: MapLoaderMaterialTextData.Font[MAPLDR_MAX_MATERIAL_TEXT_FONT_LENGTH],
    cell: MapLoaderMaterialTextData.FontSize, 
    cell: MapLoaderMaterialTextData.Bold,
    cell: MapLoaderMaterialTextData.Color,
    cell: MapLoaderMaterialTextData.BackColor, 
    cell: MapLoaderMaterialTextData.Alignment
}

//
stock cell: MapLoader.CreatedObjects[MAPLDR_MAX_OBJECTS][MapLoaderObjectData];
stock cell: MapLoader.CreatedObjectsCount;

stock cell: MapLoader.CreatedVehicles[MAPLDR_MAX_VEHICLES][MapLoaderVehicleData];
stock cell: MapLoader.CreatedVehiclesCount;

stock cell: MapLoader.Attachments[MAPLDR_MAX_VEHICLES][MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE][MapLoaderAttachmentData];
stock cell: MapLoader.AttachmentsCount[MAPLDR_MAX_VEHICLES];

stock cell: MapLoader.RemovedObjects[MAPLDR_MAX_REMOVALS][MapLoaderRemovalData];
stock cell: MapLoader.RemovedObjectsCount;

stock cell: MapLoader.ObjectMaterials[MAPLDR_MAX_OBJECTS][MAPLDR_MAX_MATERIALS_PER_OBJECT][MapLoaderMaterialData];
stock cell: MapLoader.ObjectMaterialsCount[MAPLDR_MAX_OBJECTS];

stock cell: MapLoader.ObjectMaterialTexts[MAPLDR_MAX_OBJECTS][MAPLDR_MAX_MATERIAL_TEXTS_PER_OBJECT][MapLoaderMaterialTextData];
stock cell: MapLoader.ObjectMaterialTextsCount[MAPLDR_MAX_OBJECTS];

stock cell: MapLoader.AttachmentMaterials[MAPLDR_MAX_VEHICLES][MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE][MAPLDR_MAX_MATERIALS_PER_ATTACHMENT][MapLoaderMaterialData];
stock cell: MapLoader.AttachmentMaterialsCount[MAPLDR_MAX_VEHICLES][MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE];

stock cell: MapLoader.AttachmentMaterialTexts[MAPLDR_MAX_VEHICLES][MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE][MAPLDR_MAX_MATERIAL_TEXTS_PER_ATTACHMENT][MapLoaderMaterialTextData];
stock cell: MapLoader.AttachmentMaterialTextsCount[MAPLDR_MAX_VEHICLES][MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE];

stock cell: MapLoader.TotalRemovedObjects[MAPLDR_TOTAL_MAX_REMOVALS][MapLoaderRemovalData];
stock cell: MapLoader.TotalRemovedObjectsCount;

/**
 * Clears the Map Loader cache.
 */
stock void: MapLoader.Clear()
{
    for (new i = 0; i < MAPLDR_MAX_OBJECTS; i ++)
    {
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Model] = -1;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][0] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][1] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][2] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][0] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][1] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][2] = 0.0;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.World] = -1;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.Interior] = -1;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.StreamDistance] = -1;
        MapLoader.CreatedObjects[i][MapLoaderObjectData.DrawDistance] = -1;

        for (new j = 0; j < MAPLDR_MAX_MATERIALS_PER_OBJECT; j ++)
        {
            MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Index] = -1;
            MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Model] = -1;
            format(MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Txd], MAPLDR_MAX_TXD_NAME_LENGTH, "");
            format(MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Texture], MAPLDR_MAX_TEXTURE_NAME_LENGTH, "");
            MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Color] = -1;
        }

        for (new j = 0; j < MAPLDR_MAX_MATERIAL_TEXTS_PER_OBJECT; j ++)
        {
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Index] = -1;
            format(MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Text], MAPLDR_MAX_MATERIAL_TEXT_LENGTH, "");
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Size] = -1;
            format(MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Font], MAPLDR_MAX_MATERIAL_TEXT_FONT_LENGTH, "");
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.FontSize] = -1;
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Bold] = -1;
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Color] = -1;
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.BackColor] = -1;
            MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Alignment] = -1;
        }

        MapLoader.ObjectMaterialsCount[i] = 0;
        MapLoader.ObjectMaterialTextsCount[i] = 0;
    }
    for (new i = 0; i < MAPLDR_MAX_VEHICLES; i ++)
    {
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Model] = -1;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][0] = 0.0;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][1] = 0.0;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][2] = 0.0;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Rotation] = 0.0;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Color][0] = -1;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Color][1] = -1;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Respawn] = -1;
        MapLoader.CreatedVehicles[i][MapLoaderVehicleData.AddSiren] = -1;

        for (new j = 0; j < MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE; j ++)
        {
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Model] = -1;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][0] = 0.0;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][1] = 0.0;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][2] = 0.0;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][0] = 0.0;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][1] = 0.0;
            MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][2] = 0.0;

            for (new k = 0; k < MAPLDR_MAX_MATERIALS_PER_ATTACHMENT; k ++)
            {
                MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Index] = -1;
                MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Model] = -1;
                format(MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Txd], MAPLDR_MAX_TXD_NAME_LENGTH, "");
                format(MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Texture], MAPLDR_MAX_TEXTURE_NAME_LENGTH, "");
                MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Color] = -1;
            }

            for (new k = 0; k < MAPLDR_MAX_MATERIAL_TEXTS_PER_ATTACHMENT; k ++)
            {
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Index] = -1;
                format(MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Text], MAPLDR_MAX_MATERIAL_TEXT_LENGTH, "");
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Size] = -1;
                format(MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Font], MAPLDR_MAX_MATERIAL_TEXT_FONT_LENGTH, "");
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.FontSize] = -1;
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Bold] = -1;
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Color] = -1;
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.BackColor] = -1;
                MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Alignment] = -1;
            }
            MapLoader.AttachmentMaterialsCount[i][j] = 0;
            MapLoader.AttachmentMaterialTextsCount[i][j] = 0;
        }
        MapLoader.AttachmentsCount[i] = 0;
    }
    for (new i = 0; i < MAPLDR_MAX_REMOVALS; i ++)
    {
        MapLoader.RemovedObjects[i][MapLoaderRemovalData.Model] = -1;
        MapLoader.RemovedObjects[i][MapLoaderRemovalData.Position][0] = 0.0;
        MapLoader.RemovedObjects[i][MapLoaderRemovalData.Position][1] = 0.0;
        MapLoader.RemovedObjects[i][MapLoaderRemovalData.Position][2] = 0.0;
        MapLoader.RemovedObjects[i][MapLoaderRemovalData.Radius] = 0.0;
    }

    MapLoader.CreatedObjectsCount = 0;
    MapLoader.CreatedVehiclesCount = 0;
    MapLoader.RemovedObjectsCount = 0;
}

/**
 * Parses a file in the Sasinosoft Map format. The results will be available 
 * in the MapLoader cache variables. Call MapLoader.Apply() to automatically 
 * apply the loaded results. The cache gets cleared from one call to the next.
 * @param const cell[] fileNameWithoutExtension The file name without extension.
 * @return The number of errors found.
 */
stock cell: MapLoader.Load(const cell: fileNameWithoutExtension[])
{
    #if defined MAPLDR_AUTO_CLEAR
    MapLoader.Clear();
    #endif

    new File: file;
    new cell: fileName[128];
    new cell: line[MAPLDR_MAX_LINE_LENGTH];
    new cell: errorCount;

    // sml = Sasinosoft Map Loader
    if (strfind(fileNameWithoutExtension, ".sml", true) != -1)
        format(fileName, sizeof(fileName), fileNameWithoutExtension); 
    else
        format(fileName, sizeof(fileName), "%s.sml", fileNameWithoutExtension);

    file = fopen(fileName, io_read);
    if (file)
    {
        new cell: data[254];
        new cell: lineLength;
        new cell: lineCount;
        new cell: attachmentTarget = -1;
        new cell: materialTarget = -1;
        new cell: materialTargetType = -1; // -1 null, 0 = object, 1 = attached object
        
        // Constants
        new cell: constantKeys[MAPLDR_MAX_CONSTANTS][MAPLDR_MAX_CONSTANT_KEY_LENGTH];
        new cell: constantValues[MAPLDR_MAX_CONSTANTS][MAPLDR_MAX_CONSTANT_VALUE_LENGTH];
        new cell: constantCount;

        while (fread(file, line, sizeof(line)))
        {
            lineCount ++;
            strreplace(line, "\r\n", "", false);

            lineLength = strlen(line);
            if (lineLength == 0)
                continue;

            strmid(data, line, 2, lineLength);

            for (new i = 0; i < constantCount; i ++)
            {
                strreplace(data, constantKeys[i], constantValues[i], false);
            }
            
            if (line[0] == '#') // Comment
            {
                continue;
            }
            else if (line[0] == 'K') // Constant
            {
                if (constantCount == MAPLDR_MAX_CONSTANTS)
                {
                    printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "constant");
                    errorCount ++;
                    continue;
                }

                if (sscanf(data, sprintf("s[%d]s[%d]", MAPLDR_MAX_CONSTANT_KEY_LENGTH, MAPLDR_MAX_CONSTANT_VALUE_LENGTH), constantKeys[constantCount], constantValues[constantCount]))
                {
                    printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                constantCount++;
            }
            else if (line[0] == 'C' || line[0] == 'O') // Object
            {
                if (MapLoader.CreatedObjectsCount == MAPLDR_MAX_OBJECTS)
                {
                    printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "object");
                    errorCount ++;
                    continue;
                }

                new cell: idx = MapLoader.CreatedObjectsCount;
                if (sscanf(data, sprintf("iffffffI(%d)I(%d)F(%f)F(%f)", MAPLDR_DEFAULT_VW, MAPLDR_DEFAULT_INT, MAPLDR_DEFAULT_SD, MAPLDR_DEFAULT_DD), 
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Model],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Position][0],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Position][1],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Position][2],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Rotation][0],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Rotation][1],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Rotation][2],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.World],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.Interior],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.StreamDistance],
                    MapLoader.CreatedObjects[idx][MapLoaderObjectData.DrawDistance]
                ))
                {
                    printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                attachmentTarget = -1;
                materialTarget = idx;
                materialTargetType = 0;
                MapLoader.CreatedObjectsCount ++;
            }
            else if (line[0] == 'V') // Vehicle
            {
                if (MapLoader.CreatedVehiclesCount == MAPLDR_MAX_VEHICLES)
                {
                    printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "vehicle");
                    errorCount ++;
                    continue;
                }

                new cell: idx = MapLoader.CreatedVehiclesCount;
                if (sscanf(data, sprintf("iffffI(%d)I(%d)I(%d)I(%d)", MAPLDR_DEFAULT_COL1, MAPLDR_DEFAULT_COL2, MAPLDR_DEFAULT_RESPAWN, MAPLDR_DEFAULT_ADDSIREN), 
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Model],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Position][0],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Position][1],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Position][2],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Rotation],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Color][0],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Color][1],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.Respawn],
                    MapLoader.CreatedVehicles[idx][MapLoaderVehicleData.AddSiren]
                ))
                {
                    printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                attachmentTarget = idx;
                materialTarget = -1;
                materialTargetType = -1;
                MapLoader.CreatedVehiclesCount ++;
            }
            else if (line[0] == 'R') // Remove
            {
                if (MapLoader.RemovedObjectsCount == MAPLDR_MAX_REMOVALS)
                {
                    printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "removal");
                    errorCount ++;
                    continue;
                }

                new cell: idx = MapLoader.RemovedObjectsCount;
                if (sscanf(data, "iffff", 
                    MapLoader.RemovedObjects[idx][MapLoaderRemovalData.Model],
                    MapLoader.RemovedObjects[idx][MapLoaderRemovalData.Position][0],
                    MapLoader.RemovedObjects[idx][MapLoaderRemovalData.Position][1],
                    MapLoader.RemovedObjects[idx][MapLoaderRemovalData.Position][2],
                    MapLoader.RemovedObjects[idx][MapLoaderRemovalData.Radius]
                ))
                {
                    printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                attachmentTarget = -1;
                materialTarget = -1;
                materialTargetType = -1;
                MapLoader.RemovedObjectsCount ++;
            }
            else if (line[0] == 'A') // Attached Object
            {
                if (attachmentTarget == -1)
                {
                    printf(MAPLDR_NO_OBJ_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                
                if (MapLoader.AttachmentsCount[attachmentTarget] == MAPLDR_MAX_ATTACHMENTS_PER_VEHICLE)
                {
                    printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "attachments");
                    errorCount ++;
                    continue;
                }

                new cell: idx = MapLoader.AttachmentsCount[attachmentTarget];
                if (sscanf(data, sprintf("iffffffI(%d)I(%d)F(%f)F(%f)", MAPLDR_DEFAULT_VW, MAPLDR_DEFAULT_INT, MAPLDR_DEFAULT_SD, MAPLDR_DEFAULT_DD), 
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Model],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Offset][0],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Offset][1],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Offset][2],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Rotation][0],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Rotation][1],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Rotation][2],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.World],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.Interior],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.StreamDistance],
                    MapLoader.Attachments[attachmentTarget][idx][MapLoaderAttachmentData.DrawDistance]
                ))
                {
                    printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }
                
                materialTarget = idx;
                materialTargetType = 1;
                MapLoader.AttachmentsCount[attachmentTarget] ++;
            }
            else if (line[0] == 'M') // Material
            {
                if (materialTarget == -1 || materialTargetType == -1)
                {
                    printf(MAPLDR_NO_OBJ_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }

                if (materialTargetType == 0)
                {
                    if (MapLoader.ObjectMaterialsCount[materialTarget] == MAPLDR_MAX_MATERIALS_PER_OBJECT)
                    {
                        printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "material");
                        errorCount ++;
                        continue;
                    }

                    new cell: idx = MapLoader.ObjectMaterialsCount[materialTarget];
                    if (sscanf(data, sprintf("iis[%d]s[%d]x", MAPLDR_MAX_TXD_NAME_LENGTH, MAPLDR_MAX_TEXTURE_NAME_LENGTH),
                        MapLoader.ObjectMaterials[materialTarget][idx][MapLoaderMaterialData.Index],
                        MapLoader.ObjectMaterials[materialTarget][idx][MapLoaderMaterialData.Model],
                        MapLoader.ObjectMaterials[materialTarget][idx][MapLoaderMaterialData.Txd],
                        MapLoader.ObjectMaterials[materialTarget][idx][MapLoaderMaterialData.Texture],
                        MapLoader.ObjectMaterials[materialTarget][idx][MapLoaderMaterialData.Color]
                    ))
                    {
                        printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }
                    MapLoader.ObjectMaterialsCount[materialTarget]++;
                }
                else if (materialTargetType == 1)
                {
                    if (attachmentTarget == -1)
                    {
                        printf(MAPLDR_NO_OBJ_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }

                    if (MapLoader.AttachmentMaterialsCount[attachmentTarget][materialTarget] == MAPLDR_MAX_MATERIALS_PER_ATTACHMENT)
                    {
                        printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "material per attachment");
                        errorCount ++;
                        continue;
                    }

                    new cell: idx = MapLoader.AttachmentMaterialsCount[attachmentTarget][materialTarget];
                    if (sscanf(data, sprintf("iis[%d]s[%d]x", MAPLDR_MAX_TXD_NAME_LENGTH, MAPLDR_MAX_TEXTURE_NAME_LENGTH),
                        MapLoader.AttachmentMaterials[attachmentTarget][materialTarget][idx][MapLoaderMaterialData.Index],
                        MapLoader.AttachmentMaterials[attachmentTarget][materialTarget][idx][MapLoaderMaterialData.Model],
                        MapLoader.AttachmentMaterials[attachmentTarget][materialTarget][idx][MapLoaderMaterialData.Txd],
                        MapLoader.AttachmentMaterials[attachmentTarget][materialTarget][idx][MapLoaderMaterialData.Texture],
                        MapLoader.AttachmentMaterials[attachmentTarget][materialTarget][idx][MapLoaderMaterialData.Color]
                    ))
                    {
                        printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }
                    MapLoader.AttachmentMaterialsCount[attachmentTarget][materialTarget]++;
                }
            }
            else if (line[0] == 'T') // Material Text
            {
                if (materialTarget == -1 || materialTargetType == -1)
                {
                    printf(MAPLDR_NO_OBJ_ERROR, fileName, lineCount);
                    errorCount ++;
                    continue;
                }

                new cell: formatString[128];
                format(formatString, sizeof(formatString), "is[%d]I(%d)S(%s)[%d]I(%d)I(%d)X(%x)X(%x)I(%d)",
                    MAPLDR_MAX_MATERIAL_TEXT_LENGTH,
                    MAPLDR_DEFAULT_SIZE,
                    MAPLDR_DEFAULT_FONT,
                    MAPLDR_MAX_MATERIAL_TEXT_FONT_LENGTH,
                    MAPLDR_DEFAULT_FONT_SIZE,
                    MAPLDR_DEFAULT_BOLD,
                    MAPLDR_DEFAULT_FOREGROUND,
                    MAPLDR_DEFAULT_BACKGROUND,
                    MAPLDR_DEFAULT_ALIGNMENT
                );

                if (materialTargetType == 0)
                {
                    if (MapLoader.ObjectMaterialTextsCount[materialTarget] == MAPLDR_MAX_MATERIAL_TEXTS_PER_OBJECT)
                    {
                        printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "material text");
                        errorCount ++;
                        continue;
                    }

                    new cell: idx = MapLoader.ObjectMaterialTextsCount[materialTarget];
                    if (sscanf(data, formatString, 
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Index],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Text],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Size],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Font],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.FontSize],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Bold],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Color],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.BackColor],
                        MapLoader.ObjectMaterialTexts[materialTarget][idx][MapLoaderMaterialTextData.Alignment]
                    ))
                    {
                        printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }
                    MapLoader.ObjectMaterialTextsCount[materialTarget] ++;
                }
                else if (materialTargetType == 1)
                {
                    if (attachmentTarget == -1)
                    {
                        printf(MAPLDR_NO_OBJ_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }

                    if (MapLoader.AttachmentMaterialTextsCount[attachmentTarget][materialTarget] == MAPLDR_MAX_MATERIAL_TEXTS_PER_ATTACHMENT)
                    {
                        printf(MAPLDR_LIMIT_ERROR, fileName, lineCount, "material text per attachment");
                        errorCount ++;
                        continue;
                    }

                    new cell: idx = MapLoader.AttachmentMaterialTextsCount[attachmentTarget][materialTarget];
                    if (sscanf(data, formatString, 
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Index],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Text],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Size],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Font],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.FontSize],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Bold],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Color],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.BackColor],
                        MapLoader.AttachmentMaterialTexts[attachmentTarget][materialTarget][idx][MapLoaderMaterialTextData.Alignment]
                    ))
                    {
                        printf(MAPLDR_FORMAT_ERROR, fileName, lineCount);
                        errorCount ++;
                        continue;
                    }
                    MapLoader.AttachmentMaterialTextsCount[attachmentTarget][materialTarget] ++;
                }
            }
            else
            {
                printf(MAPLDR_DIRECTIVE_ERROR, fileName, lineCount, line[0]);
                errorCount ++;
            }
        }
        fclose(file);

        if (errorCount > 0)
        {
            printf(MAPLDR_ERRORS, fileName, errorCount);
        }
    }
    else
    {
        printf(MAPLDR_FILE_ERROR, fileName);
    }
    return errorCount;
}

///
stock void: MapLoader.Apply()
{
    for (new i = 0; i < MapLoader.CreatedObjectsCount; i ++)
    {
        new cell: objectId;

        #if defined _streamer_included
        objectId = CreateDynamicObject(
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Model], 
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][0],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][1],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][2],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][0],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][1],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][2],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.World],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Interior],
            -1, 
            MapLoader.CreatedObjects[i][MapLoaderObjectData.StreamDistance], 
            MapLoader.CreatedObjects[i][MapLoaderObjectData.DrawDistance], 
            -1
        );
        #else
        objectId = CreateObject(
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Model],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][0],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][1],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Position][2],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][0],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][1],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.Rotation][2],
            MapLoader.CreatedObjects[i][MapLoaderObjectData.DrawDistance]
        );
        #endif

        for (new j = 0; j < MapLoader.ObjectMaterialsCount[i]; j ++)
        {
            #if defined _streamer_included
            SetDynamicObjectMaterial(
                objectId, 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Index], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Model], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Txd], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Texture], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Color]
            );
            #else
            SetObjectMaterial(
                objectId, 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Index], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Model], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Txd], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Texture], 
                MapLoader.ObjectMaterials[i][j][MapLoaderMaterialData.Color]
            );
            #endif
        }

        for (new j = 0; j < MapLoader.ObjectMaterialTextsCount[i]; j ++)
        {
            #if defined _streamer_included
            SetDynamicObjectMaterialText(
                objectId, 
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Index],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Text],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Size],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Font],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.FontSize],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Bold],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Color],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.BackColor],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Alignment]
            );
            #else
            SetObjectMaterialText(
                objectId, 
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Text],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Index],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Size],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Font],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.FontSize],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Bold],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Color],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.BackColor],
                MapLoader.ObjectMaterialTexts[i][j][MapLoaderMaterialTextData.Alignment]
            );
            #endif
        }
    }

    for (new i = 0; i < MapLoader.CreatedVehiclesCount; i ++)
    {
        new cell: vehicleId;
        vehicleId = CreateVehicle(
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Model],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][0],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][1],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Position][2],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Rotation],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Color][0],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Color][1],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.Respawn],
            MapLoader.CreatedVehicles[i][MapLoaderVehicleData.AddSiren]
        );

        for (new j = 0; j < MapLoader.AttachmentsCount[i]; j ++)
        {
            new cell: objectId;
            #if defined _streamer_included
            objectId = CreateDynamicObject(
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Model], 
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.World],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Interior],
                -1, 
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.StreamDistance], 
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.DrawDistance], 
                -1
            );
            #else
            objectId = CreateObject(
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Model],
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.DrawDistance]
            );
            #endif

            for (new k = 0; k < MapLoader.AttachmentMaterialsCount[i][j]; k ++)
            {
                #if defined _streamer_included
                SetDynamicObjectMaterial(
                    objectId, 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Index], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Model], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Txd], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Texture], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Color]
                );
                #else
                SetObjectMaterial(
                    objectId, 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Index], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Model], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Txd], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Texture], 
                    MapLoader.AttachmentMaterials[i][j][k][MapLoaderMaterialData.Color]
                );
                #endif
            }
            
            for (new k = 0; k < MapLoader.AttachmentMaterialTextsCount[i][j]; k ++)
            {
                #if defined _streamer_included
                SetDynamicObjectMaterialText(
                    objectId, 
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Index],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Text],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Size],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Font],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.FontSize],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Bold],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Color],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.BackColor],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Alignment]
                );
                #else
                SetObjectMaterialText(
                    objectId, 
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Text],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Index],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Size],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Font],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.FontSize],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Bold],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Color],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.BackColor],
                    MapLoader.AttachmentMaterialTexts[i][j][k][MapLoaderMaterialTextData.Alignment]
                );
                #endif
            }
            #if defined _streamer_included
            AttachDynamicObjectToVehicle(
                objectId,
                vehicleId, 
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][0],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][1],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][2],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][0],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][1],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][2]
            );
            
            #else
            AttachObjectToVehicle(
                objectId,
                vehicleId, 
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][0],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][1],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Offset][2],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][0],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][1],
                MapLoader.Attachments[i][j][MapLoaderAttachmentData.Rotation][2]
            );
            #endif
        }
    }
        
    for (new i = 0; i < MapLoader.RemovedObjectsCount; i ++)
    {
        new cell: index = MapLoader.TotalRemovedObjectsCount;
        MapLoader.TotalRemovedObjects[index] = MapLoader.RemovedObjects[i];
        MapLoader.TotalRemovedObjectsCount++;
    }
}

/**
 * Applies the object removal for a player. Call this function in OnPlayerSpawn.
 */
stock void: MapLoader.RemoveForPlayer(cell: playerId)
{
    if (GetPVarInt(playerId, "MapLoaderRemoved") == 1)
        return;

    TogglePlayerControllable(playerId, false);
    for (new i = 0; i < MapLoader.TotalRemovedObjectsCount; i++)
    {
        RemoveBuildingForPlayer(
                playerId,
                MapLoader.TotalRemovedObjects[i][MapLoaderRemovalData.Model], 
                MapLoader.TotalRemovedObjects[i][MapLoaderRemovalData.Position][0], 
                MapLoader.TotalRemovedObjects[i][MapLoaderRemovalData.Position][1], 
                MapLoader.TotalRemovedObjects[i][MapLoaderRemovalData.Position][2], 
                MapLoader.TotalRemovedObjects[i][MapLoaderRemovalData.Radius] 
        );
    }
    TogglePlayerControllable(playerId, true);
    SetPVarInt(playerId, "MapLoaderRemoved", 1);
}
