/*
 * Sasinosoft Map Loader
 * Copyright (c) 2019-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
namespace Sasinosoft.SMLLoader
{
    public class MaterialData : IObjectData
    {
        public readonly int Index;
        public readonly int Model;
        public readonly string DictionaryName;
        public readonly string TextureName;
        public readonly int Color;

        public MaterialData(int index, int model, string dictionaryName, string textureName, int color)
        {
            Index = index;
            Model = model;
            DictionaryName = dictionaryName;
            TextureName = textureName;
            Color = color;
        }
    }
}
