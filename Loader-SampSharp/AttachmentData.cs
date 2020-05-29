/*
 * Sasinosoft Map Loader
 * Copyright (c) 2019-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
using SampSharp.GameMode;
using System.Collections.Generic;

namespace Sasinosoft.SMLLoader
{
    public class AttachmentData : IObjectData
    {
        public readonly int Model;
        public readonly Vector3 Offset;
        public readonly Vector3 Rotation;
        public readonly int VirtualWorld;
        public readonly int Interior;
        public readonly float StreamDistance;
        public readonly float DrawDistance;

        public readonly List<MaterialData> Materials;
        public readonly List<MaterialTextData> MaterialTexts;

        public AttachmentData(int model, Vector3 offset, Vector3 rotation, int virtualWorld, int interior, float streamDistance, float drawDistance)
        {
            Model = model;
            Offset = offset;
            Rotation = rotation;
            VirtualWorld = virtualWorld;
            Interior = interior;
            StreamDistance = streamDistance;
            DrawDistance = drawDistance;
            Materials = new List<MaterialData>();
            MaterialTexts = new List<MaterialTextData>();
        }
    }
}
