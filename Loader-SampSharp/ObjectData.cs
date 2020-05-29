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
using System.Linq;

namespace Sasinosoft.SMLLoader
{
    public class ObjectData : IObjectData
    {
        public readonly int Model;
        public readonly Vector3 Position;
        public readonly Vector3 Rotation;
        public readonly HashSet<int> VirtualWorlds;
        public readonly HashSet<int> Interiors;
        public readonly float StreamDistance;
        public readonly float DrawDistance;
        public readonly int Priority;

        public readonly List<MaterialData> Materials;
        public readonly List<MaterialTextData> MaterialTexts;

        public ObjectData(int model, Vector3 position, Vector3 rotation, 
            IEnumerable<int> virtualWorlds, IEnumerable<int> interiors, 
            float streamDistance, float drawDistance, int priority)
        {
            Model = model;
            Position = position;
            Rotation = rotation;
            VirtualWorlds = virtualWorlds.ToHashSet();
            Interiors = interiors.ToHashSet();
            StreamDistance = streamDistance;
            DrawDistance = drawDistance;
            Priority = priority;
            Materials = new List<MaterialData>();
            MaterialTexts = new List<MaterialTextData>();
        }
    }
}
