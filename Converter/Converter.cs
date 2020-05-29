/*
 * Sasinosoft Map Converter
 * Copyright (c) 2017-2020 - Sasinosoft
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */
using System;
using System.Collections.Generic;
using System.IO;

namespace Sasinosoft.MapConverter
{
    static class Converter
    {
        internal static bool Convert(string fileName)
        {
            if (Path.GetExtension(fileName).EndsWith(".sml"))
                return ConvertToPawn(fileName);

            else if (Path.GetExtension(fileName).EndsWith(".pwn"))
                return ConvertToSML(fileName);

            return false;
        }

        static bool ConvertToSML(string fileName)
        {
            try
            {

                string content = File.ReadAllText(fileName);
                string[] lines = content.Split('\n');
                string output = "# Converted by Sasinosoft Map Converter\n\n# Constants\nK DefaultInterior -1\nK DefaultVW -1\nK DefaultStreamDist 200.0\nK DefaultDrawDist 200.0\n\n# Scene data\n";

                foreach (string line_ in lines)
                {
                    string line = line_.Trim(' ', '\r', '\t');

                    if (line.StartsWith("CreateObject") || line.StartsWith("CreateDynamicObject"))
                    {
                        output += "C ";

                        int startIdx = line.IndexOf('(');
                        int endIdx = line.IndexOf(')');
                        string rawData = line.Substring(startIdx, endIdx - startIdx);
                        string[] values = rawData.Split(',');

                        output += values[0].Trim(' ', '(', ')') + " ";
                        output += values[1].Trim(' ', '(', ')') + " ";
                        output += values[2].Trim(' ', '(', ')') + " ";
                        output += values[3].Trim(' ', '(', ')') + " ";
                        output += values[4].Trim(' ', '(', ')') + " ";
                        output += values[5].Trim(' ', '(', ')') + " ";
                        output += values[6].Trim(' ', '(', ')') + " ";

                        output += "DefaultVW DefaultInterior DefaultStreamDist DefaultDrawDist\n";
                    }
                    else if (line.StartsWith("CreateVehicle"))
                    {
                        output += "V ";

                        int startIdx = line.IndexOf('(');
                        int endIdx = line.IndexOf(')');
                        string rawData = line.Substring(startIdx, endIdx - startIdx);
                        string[] values = rawData.Split(',');

                        output += values[0].Trim(' ', '(', ')') + " ";
                        output += values[1].Trim(' ', '(', ')') + " ";
                        output += values[2].Trim(' ', '(', ')') + " ";
                        output += values[3].Trim(' ', '(', ')') + " ";
                        output += values[4].Trim(' ', '(', ')') + " ";
                        output += values[5].Trim(' ', '(', ')') + " ";
                        output += values[6].Trim(' ', '(', ')') + "\n";
                    }
                    else if (line.StartsWith("RemoveBuildingForPlayer"))
                    {
                        output += "R ";

                        int startIdx = line.IndexOf('(');
                        int endIdx = line.IndexOf(')');
                        string rawData = line.Substring(startIdx, endIdx - startIdx);
                        string[] values = rawData.Split(',');

                        output += values[1].Trim(' ', '(', ')') + " ";
                        output += values[2].Trim(' ', '(', ')') + " ";
                        output += values[3].Trim(' ', '(', ')') + " ";
                        output += values[4].Trim(' ', '(', ')') + " ";
                        output += values[5].Trim(' ', '(', ')') + "\n";
                    }
                }
                output += "\n# End of file";

                string newFileName = Path.Combine(Path.GetDirectoryName(fileName), Path.GetFileNameWithoutExtension(fileName)+ ".sml");
                File.WriteAllText(newFileName, output);
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return false;
            }
        }

        static bool ConvertToPawn(string fileName)
        {
            try
            {
                string content = File.ReadAllText(fileName);
                string[] lines = content.Split('\n');

                string output = "// Converted by Sasinosoft Map Converter\n\n";

                var constants = new Dictionary<string, string>();

                foreach (string line_ in lines)
                {
                    string line = line_.Trim(' ', '\r', '\t');

                    foreach (string k in constants.Keys)
                        line = line.Replace(k, constants[k]);

                    line = line.Replace("  ", " ");

                    if (line.StartsWith("C"))
                    {
                        output += "CreateObject(";

                        int startIdx = line.IndexOf(' ') + 1;
                        string rawData = line.Substring(startIdx);
                        string[] values = rawData.Split(' ');

                        output += values[0].Trim(' ', '(', ')') + ", ";
                        output += values[1].Trim(' ', '(', ')') + ", ";
                        output += values[2].Trim(' ', '(', ')') + ", ";
                        output += values[3].Trim(' ', '(', ')') + ", ";
                        output += values[4].Trim(' ', '(', ')') + ", ";
                        output += values[5].Trim(' ', '(', ')') + ", ";
                        output += values[6].Trim(' ', '(', ')') + ");\n";
                    }
                    else if (line.StartsWith("V"))
                    {
                        output += "CreateVehicle(";

                        int startIdx = line.IndexOf(' ') + 1;
                        string rawData = line.Substring(startIdx);
                        string[] values = rawData.Split(' ');

                        output += values[0].Trim(' ', '(', ')') + ", ";
                        output += values[1].Trim(' ', '(', ')') + ", ";
                        output += values[2].Trim(' ', '(', ')') + ", ";
                        output += values[3].Trim(' ', '(', ')') + ", ";
                        output += values[4].Trim(' ', '(', ')') + ", ";
                        output += values[5].Trim(' ', '(', ')') + ", ";
                        output += values[6].Trim(' ', '(', ')') + ");\n";
                    }
                    else if (line.StartsWith("R"))
                    {
                        output += "RemoveBuildingForPlayer(playerid, ";

                        int startIdx = line.IndexOf(' ') + 1;
                        string rawData = line.Substring(startIdx);
                        string[] values = rawData.Split(' ');

                        output += values[0].Trim(' ', '(', ')') + ", ";
                        output += values[1].Trim(' ', '(', ')') + ", ";
                        output += values[2].Trim(' ', '(', ')') + ", ";
                        output += values[3].Trim(' ', '(', ')') + ", ";
                        output += values[4].Trim(' ', '(', ')') + ");\n";
                    }
                    else if (line.StartsWith("K"))
                    {
                        int startIdx = line.IndexOf(' ') + 1;
                        string rawData = line.Substring(startIdx);
                        string[] values = rawData.Split(' ');

                        if (!constants.ContainsKey(values[0]))
                            constants.Add(values[0], values[1]);
                    }
                }

                string newFileName = Path.Combine(Path.GetDirectoryName(fileName), Path.GetFileNameWithoutExtension(fileName) + ".pwn");
                File.WriteAllText(newFileName, output);
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return false;
            }
        }
    }
}
