/*
 * Sasinosoft Map Loader
 * Copyright (c) 2019-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
using SampSharp.GameMode;

namespace Sasinosoft.SMLLoader
{
    public class RemovalData : IObjectData
    {
        public readonly int Model;
        public readonly Vector3 Position;
        public readonly float Range;

        public RemovalData(int model, Vector3 position, float range)
        {
            Model = model;
            Position = position;
            Range = range;
        }
    }
}
