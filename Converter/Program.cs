/*
 * Sasinosoft Map Converter
 * Copyright (c) 2017-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
using System;
using System.IO;

namespace Sasinosoft.MapConverter
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length <= 0)
            {
                Console.WriteLine("Error: no file specified.");
                return;
            }

            foreach (string arg in args)
            {
                if (File.Exists(arg))
                {
                    if (!Converter.Convert(arg))
                        Console.WriteLine($"Warning: couldn't convert file '{arg}'.");
                }
                else
                {
                    Console.WriteLine($"Warning: file '{arg}' does not exist.");
                }
            }
        }
    }
}
