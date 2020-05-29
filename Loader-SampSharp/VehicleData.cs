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
    public class VehicleData : IObjectData
    {
        public readonly int Model;
        public readonly Vector3 Position;
        public readonly float Rotation;
        public readonly int Color1;
        public readonly int Color2;
        public readonly int Respawn;
        public readonly int Siren;
        public readonly int VirtualWorld;
        public readonly int Interior;

        public readonly List<AttachmentData> Attachments;

        public VehicleData(int model, Vector3 position, float rotation, int color1, int color2, int respawn, int siren, int virtualWorld, int interior)
        {
            Model = model;
            Position = position;
            Rotation = rotation;
            Color1 = color1;
            Color2 = color2;
            Respawn = respawn;
            Siren = siren;
            VirtualWorld = virtualWorld;
            Interior = interior;
            Attachments = new List<AttachmentData>();
        }
    }
}
