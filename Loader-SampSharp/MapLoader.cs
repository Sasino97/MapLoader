/*
 * Sasinosoft Map Loader
 * Copyright (c) 2019-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
using SampSharp.GameMode;
using SampSharp.GameMode.Definitions;
using SampSharp.GameMode.World;
using SampSharp.Streamer.World;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;

namespace Sasinosoft.SMLLoader
{
    public class MapLoader
    {
        //
        public static List<RemovalData> GlobalRemovals { get; private set; } = new List<RemovalData>();

        //
        public bool AutoClear { get; set; } = false;

        //
        public List<ObjectData> Objects { get; private set; }
        public List<VehicleData> Vehicles { get; private set; }
        public List<RemovalData> Removals { get; private set; }

        /// <summary>
        /// Creates a new instance of the SML map loader.
        /// </summary>
        public MapLoader()
        {
            Clear();
        }

        /// <summary>
        /// Creates a new instance of the SML map loader.
        /// </summary>
        /// <param name="autoClear">Specifies whether to automatically clear the cache at each Load() call.</param>
        public MapLoader(bool autoClear) : this()
        {
            AutoClear = autoClear;
        }

        /// <summary>
        /// Clears the loader cache.
        /// </summary>
        public void Clear()
        {
            Objects = new List<ObjectData>();
            Vehicles = new List<VehicleData>();
            Removals = new List<RemovalData>();
        }

        /// <summary>
        /// Loads a Map from a file in the SML format.
        /// </summary>
        /// <returns>The number of valid instructions found.</returns>
        public int Load(string fileName, out List<Exception> errors)
        {
            //
            if (AutoClear)
                Clear();

            //
            Dictionary<string, string> constants = new Dictionary<string, string>();

            //
            int lineCount = 0;
            errors = new List<Exception>();

            //
            string fileContent = File.ReadAllText(fileName);
            fileContent = fileContent.Replace("\r\n", "\n");
            string[] lines = fileContent.Split("\n");

            //
            IObjectData attachmentTarget = null;
            IObjectData materialTarget = null;

            //
            foreach (string line_ in lines)
            {
                string line = line_;

                if (line.Length < 1)
                    continue;

                lineCount++;

                //
                foreach (string k in constants.Keys)
                {
                    line = line.Replace(k, constants[k]);
                }

                //
                char directive = line[0];
                string data = line.Substring(1);
                
                //
                try
                {
                    if (directive == '#')
                    {
                        continue;
                    }
                    else if (directive == 'K')
                    {
                        string[] parts = SplitLine(data);
                        string key = parts[0];
                        string val = parts[1];

                        if (!constants.ContainsKey(key))
                            constants.Add(key, val);
                    }
                    else if (directive == 'C' || directive == 'O')
                    {
                        string[] parts = SplitLine(data);
                        int model = int.Parse(parts[0]);

                        Vector3 pos = new Vector3(
                            float.Parse(parts[1]),
                            float.Parse(parts[2]),
                            float.Parse(parts[3])
                        );

                        Vector3 rot = new Vector3(
                            float.Parse(parts[4]),
                            float.Parse(parts[5]),
                            float.Parse(parts[6])
                        );

                        // Optional
                        IEnumerable<int> virtualWorlds = new List<int>();
                        IEnumerable<int> interiors = new List<int>();
                        float streamDistance = 0;
                        float drawDistance = 0;
                        int priority = 0;

                        if (parts.Length >= 8) virtualWorlds = ParseIntegerArraySection(parts[7]);
                        if (parts.Length >= 9) interiors = ParseIntegerArraySection(parts[8]);
                        if (parts.Length >= 10) streamDistance = float.Parse(parts[9]);
                        if (parts.Length >= 11) drawDistance = float.Parse(parts[10]);
                        if (parts.Length >= 12) priority = int.Parse(parts[11]);


                        // Create data container object
                        var obj = new ObjectData(
                            model,
                            pos,
                            rot,
                            virtualWorlds,
                            interiors,
                            streamDistance,
                            drawDistance,
                            priority
                        );
                        Objects.Add(obj);

                        attachmentTarget = null;
                        materialTarget = obj;
                    }
                    else if (directive == 'V')
                    {
                        string[] parts = SplitLine(data);
                        int model = int.Parse(parts[0]);

                        Vector3 pos = new Vector3(
                            float.Parse(parts[1]),
                            float.Parse(parts[2]),
                            float.Parse(parts[3])
                        );

                        float rot = float.Parse(parts[4]);

                        // Optional
                        int color1 = -1;
                        int color2 = -1;
                        int respawn = -1;
                        int siren = 0;
                        int virtualWorld = 0;
                        int interior = 0;

                        if (parts.Length >= 6) color1 = int.Parse(parts[5]);
                        if (parts.Length >= 7) color2 = int.Parse(parts[6]);
                        if (parts.Length >= 8) respawn = int.Parse(parts[7]);
                        if (parts.Length >= 9) siren = int.Parse(parts[8]);
                        if (parts.Length >= 10) virtualWorld = int.Parse(parts[9]);
                        if (parts.Length >= 11) interior = int.Parse(parts[10]);

                        var veh = new VehicleData(
                            model,
                            pos,
                            rot,
                            color1,
                            color2,
                            respawn,
                            siren,
                            virtualWorld,
                            interior
                        );
                        Vehicles.Add(veh);

                        attachmentTarget = veh;
                        materialTarget = null;
                    }
                    else if (directive == 'R')
                    {
                        string[] parts = SplitLine(data);
                        int model = int.Parse(parts[0]);

                        Vector3 pos = new Vector3(
                            float.Parse(parts[1]),
                            float.Parse(parts[2]),
                            float.Parse(parts[3])
                        );

                        float radius = float.Parse(parts[4]);

                        var rem = new RemovalData(
                            model,
                            pos,
                            radius
                        );
                        Removals.Add(rem);

                        attachmentTarget = null;
                        materialTarget = null;
                    }
                    else if (directive == 'A')
                    {
                        string[] parts = SplitLine(data);
                        int model = int.Parse(parts[0]);

                        Vector3 off = new Vector3(
                            float.Parse(parts[1]),
                            float.Parse(parts[2]),
                            float.Parse(parts[3])
                        );

                        Vector3 rot = new Vector3(
                            float.Parse(parts[4]),
                            float.Parse(parts[5]),
                            float.Parse(parts[6])
                        );

                        int virtualWorld = 0;
                        int interior = 0;
                        float streamDistance = 0;
                        float drawDistance = 0;

                        // Optional
                        if (parts.Length >= 8) virtualWorld = int.Parse(parts[7]);
                        if (parts.Length >= 9) interior = int.Parse(parts[8]);
                        if (parts.Length >= 10) streamDistance = float.Parse(parts[9]);
                        if (parts.Length >= 11) drawDistance = float.Parse(parts[10]);

                        var att = new AttachmentData(
                            model,
                            off,
                            rot,
                            virtualWorld,
                            interior,
                            streamDistance,
                            drawDistance
                        );

                        ((VehicleData)attachmentTarget).Attachments.Add(att);
                        materialTarget = att;
                    }
                    else if (directive == 'M')
                    {
                        string[] parts = SplitLine(data);

                        int index = int.Parse(parts[0]);
                        int model = int.Parse(parts[1]);
                        string dictionary = parts[2];
                        string texture = parts[3];
                        int color = (int)new Int32Converter().ConvertFromString(parts[4]);

                        var att = new MaterialData(
                            index,
                            model,
                            dictionary,
                            texture,
                            color
                        );

                        if (materialTarget is ObjectData od)
                            od.Materials.Add(att);

                        else if (materialTarget is AttachmentData ad)
                            ad.Materials.Add(att);
                    }
                    else if (directive == 'T')
                    {
                        string[] parts = SplitLine(data);

                        int index = int.Parse(parts[0]);
                        string text = parts[1];
                        int size = int.Parse(parts[2]);
                        string font = parts[3];
                        int fontSize = int.Parse(parts[4]);
                        int bold = int.Parse(parts[5]);
                        int color = (int)new Int32Converter().ConvertFromString(parts[6]);
                        int backColor = (int)new Int32Converter().ConvertFromString(parts[7]);
                        int alignment = int.Parse(parts[8]);

                        var txt = new MaterialTextData(
                            index,
                            text,
                            size,
                            font,
                            fontSize,
                            bold,
                            color,
                            backColor,
                            alignment
                        );

                        if (materialTarget is ObjectData od)
                            od.MaterialTexts.Add(txt);

                        else if (materialTarget is AttachmentData ad)
                            ad.MaterialTexts.Add(txt);
                    }
                    else
                    {
                        throw new Exception($"Unknown directive '{directive}'.");
                    }
                }
                catch (Exception e)
                {
                    errors.Add(e);
                    continue;
                }
            }
            return lineCount;
        }

        /// <summary>
        /// Applies the currently cached map.
        /// </summary>
        public void Apply()
        {
            try
            {
                foreach (ObjectData obj in Objects)
                {
                    try
                    {
                        var dynamicObject = new DynamicObject(
                            obj.Model,
                            obj.Position,
                            obj.Rotation,
                            obj.StreamDistance,
                            obj.VirtualWorlds.ToArray(),
                            obj.Interiors.ToArray(),
                            null,
                            obj.DrawDistance,
                            null,
                            obj.Priority
                        );

                        foreach (MaterialData mat in obj.Materials)
                        {
                            dynamicObject.SetMaterial(
                                mat.Index,
                                mat.Model,
                                mat.DictionaryName,
                                mat.TextureName,
                                mat.Color
                            );
                        }

                        foreach (MaterialTextData txt in obj.MaterialTexts)
                        {
                            dynamicObject.SetMaterialText(
                                txt.Index,
                                txt.Text,
                                (ObjectMaterialSize)txt.Size,
                                txt.Font,
                                txt.FontSize,
                                txt.Bold == 1,
                                txt.Color,
                                txt.BackgroundColor,
                                (ObjectMaterialTextAlign)txt.Alignment
                            );
                        }
                    }
                    catch { }
                }

                foreach (VehicleData veh in Vehicles)
                {
                    try
                    {
                        int col1 = veh.Color1;
                        int col2 = veh.Color2;

                        if (col1 == -1)
                            col1 = new Random().Next(256);

                        if (col2 == -1)
                            col2 = new Random().Next(256);

                        var vehicle = BaseVehicle.Create(
                            (VehicleModelType)veh.Model,
                            veh.Position,
                            veh.Rotation,
                            col1,
                            col2,
                            veh.Respawn,
                            veh.Siren != 0
                        );

                        vehicle.VirtualWorld = veh.VirtualWorld;
                        vehicle.LinkToInterior(veh.Interior);

                        foreach (AttachmentData att in veh.Attachments)
                        {
                            var dynamicObject = new DynamicObject(
                                att.Model,
                                new Vector3(),
                                new Vector3(),
                                att.VirtualWorld,
                                att.Interior,
                                null,
                                att.StreamDistance,
                                att.DrawDistance,
                                null,
                                0
                            );
                            dynamicObject.AttachTo(vehicle, att.Offset, att.Rotation);

                            foreach (MaterialData mat in att.Materials)
                            {
                                dynamicObject.SetMaterial(
                                    mat.Index,
                                    mat.Model,
                                    mat.DictionaryName,
                                    mat.TextureName,
                                    mat.Color
                                );
                            }

                            foreach (MaterialTextData txt in att.MaterialTexts)
                            {
                                dynamicObject.SetMaterialText(
                                    txt.Index,
                                    txt.Text,
                                    (ObjectMaterialSize)txt.Size,
                                    txt.Font,
                                    txt.FontSize,
                                    txt.Bold == 1,
                                    txt.Color,
                                    txt.BackgroundColor,
                                    (ObjectMaterialTextAlign)txt.Alignment
                                );
                            }
                        }
                    }
                    catch { }
                }

                foreach (RemovalData rem in Removals)
                {
                    GlobalRemovals.Add(rem);
                }
            }
            catch (Exception e)
            {
                var x = e;
            }
        }

        public static void ApplyRemovals(BasePlayer p)
        {
            foreach (RemovalData rem in GlobalRemovals)
            {
                try
                {
                    GlobalObject.Remove(p, rem.Model, rem.Position, rem.Range);
                }
                catch { }
            }
        }

        private string[] SplitLine(string data, char sep = ' ', char esc = '\\')
        {
            data = data.Trim();

            List<string> ret = new List<string>();
            char prevChar = (char)0;
            string str = "";

            foreach (char c in data)
            {
                if (c == sep && prevChar != esc)
                {
                    if (!string.IsNullOrWhiteSpace(str))
                        ret.Add(str.Trim());
                    str = "";
                }
                else
                    str += c;

                prevChar = c;
            }
            if (!string.IsNullOrWhiteSpace(str))
                ret.Add(str.Trim());

            return ret.ToArray();
        }

        // Parses an integer array; allows integer ranges using the - character
        // must be enclosed in [square brackets] otherwise only 1 value is parsed
        // examples: 
        // [1,3,5-7] => { 1, 3, 5, 6, 7 }
        // 15 => { 15 }
        private IEnumerable<int> ParseIntegerArraySection(string str)
        {
            var ret = new HashSet<int>();
            if (str.StartsWith('[') && str.EndsWith(']'))
            {
                var subStrings = str.TrimStart('[').TrimEnd(']').Split(',');
                foreach (var sub in subStrings)
                {
                    if (int.TryParse(sub, out int s))
                        ret.Add(s);

                    else
                    {
                        // range
                        if (sub.Contains("-"))
                        {
                            var rangeParts = sub.Split('-');
                            var first = rangeParts.First();
                            var last = rangeParts.Last();

                            if (int.TryParse(first, out int f) && int.TryParse(last, out int l) && f <= l)
                            {
                                for (int i = f; i <= l; i++)
                                    ret.Add(i);
                            }
                        }
                    }
                }
            }
            else
                ret.Add(int.Parse(str));

            return ret;
        }
    }
}
