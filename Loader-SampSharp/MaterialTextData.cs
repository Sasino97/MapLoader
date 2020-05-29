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
    public class MaterialTextData : IObjectData
    {
        public readonly int Index;
        public readonly string Text;
        public readonly int Size;
        public readonly string Font;
        public readonly int FontSize;
        public readonly int Bold;
        public readonly int Color;
        public readonly int BackgroundColor;
        public readonly int Alignment;

        public MaterialTextData(int index, string text, int size, string font, int fontSize, int bold, int color, int backgroundColor, int alignment)
        {
            Index = index;
            Text = text;
            Size = size;
            Font = font;
            FontSize = fontSize;
            Bold = bold;
            Color = color;
            BackgroundColor = backgroundColor;
            Alignment = alignment;
        }
    }
}
