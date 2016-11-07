xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 179;
 0.00000;-0.00000;-0.00000;,
 0.00000;-1.14805;-2.77164;,
 0.00000;-0.00000;-3.00000;,
 0.00000;-2.12132;-2.12132;,
 0.00000;-2.77164;-1.14805;,
 0.00000;-3.00000;0.00000;,
 0.00000;-2.77164;1.14805;,
 0.00000;-2.12132;2.12132;,
 0.00000;-1.14805;2.77164;,
 0.00000;-0.00000;3.00000;,
 0.00000;1.14805;2.77164;,
 0.00000;2.12132;2.12132;,
 0.00000;2.77164;1.14805;,
 0.00000;3.00000;-0.00000;,
 0.00000;2.77164;-1.14805;,
 0.00000;2.12132;-2.12132;,
 0.00000;1.14805;-2.77164;,
 0.00000;-0.00000;-3.00000;,
 0.00000;-1.14805;-2.77164;,
 -0.15224;-1.44094;-3.47875;,
 -0.15224;-0.00000;-3.76537;,
 0.00000;-2.12132;-2.12132;,
 -0.15224;-2.66252;-2.66252;,
 0.00000;-2.77164;-1.14805;,
 -0.15224;-3.47875;-1.44094;,
 -0.15224;-3.76537;0.00000;,
 -0.15224;-3.47875;1.44094;,
 -0.15224;-3.76537;0.00000;,
 -0.15224;-2.66252;2.66252;,
 -0.15224;-1.44094;3.47875;,
 -0.15224;-0.00000;3.76537;,
 -0.15224;1.44094;3.47875;,
 -0.15224;2.66252;2.66252;,
 -0.15224;3.47874;1.44094;,
 0.00000;3.00000;-0.00000;,
 -0.15224;3.76537;-0.00000;,
 0.00000;2.77164;-1.14805;,
 -0.15224;3.47874;-1.44094;,
 -0.15224;3.76537;-0.00000;,
 0.00000;2.12132;-2.12132;,
 -0.15224;2.66252;-2.66252;,
 0.00000;1.14805;-2.77164;,
 -0.15224;1.44094;-3.47875;,
 -0.15224;-0.00000;-3.76537;,
 -0.15224;-1.44094;-3.47875;,
 -0.58579;-1.68925;-4.07820;,
 -0.58579;-0.00000;-4.41421;,
 -0.15224;-2.66252;-2.66252;,
 -0.58579;-3.12132;-3.12132;,
 -0.15224;-3.47875;-1.44094;,
 -0.58579;-4.07820;-1.68925;,
 -0.58579;-4.41421;0.00000;,
 -0.58579;-4.07820;1.68925;,
 -0.58579;-3.12132;3.12132;,
 -0.58579;-1.68925;4.07820;,
 -0.58579;-0.00000;4.41421;,
 -0.58579;1.68925;4.07820;,
 -0.58579;3.12132;3.12132;,
 -0.58579;4.07820;1.68925;,
 -0.58579;4.41421;-0.00000;,
 -0.15224;3.47874;-1.44094;,
 -0.58579;4.07820;-1.68925;,
 -0.15224;2.66252;-2.66252;,
 -0.58579;3.12132;-3.12132;,
 -0.15224;1.44094;-3.47875;,
 -0.58579;1.68924;-4.07820;,
 -1.23463;-1.85516;-4.47875;,
 -1.23463;-0.00000;-4.84776;,
 -1.23463;-3.42788;-3.42788;,
 -1.23463;-4.47875;-1.85516;,
 -1.23463;-4.84776;0.00000;,
 -1.23463;-4.47875;1.85516;,
 -1.23463;-3.42788;3.42788;,
 -1.23463;-1.85516;4.47875;,
 -1.23463;-0.00000;4.84776;,
 -1.23463;1.85516;4.47875;,
 -1.23463;3.42788;3.42788;,
 -1.23463;4.47875;1.85516;,
 -1.23463;4.84776;-0.00000;,
 -1.23463;4.47875;-1.85516;,
 -1.23463;3.42788;-3.42788;,
 -1.23463;1.85515;-4.47875;,
 -2.00000;-1.91342;-4.61940;,
 -2.00000;-0.00000;-5.00000;,
 -2.00000;-3.53553;-3.53553;,
 -2.00000;-4.61940;-1.91342;,
 -2.00000;-5.00000;0.00000;,
 -2.00000;-4.61940;1.91342;,
 -2.00000;-3.53553;3.53553;,
 -2.00000;-1.91342;4.61940;,
 -2.00000;-0.00000;5.00000;,
 -2.00000;1.91342;4.61940;,
 -2.00000;3.53553;3.53554;,
 -2.00000;4.61940;1.91342;,
 -2.00000;5.00000;-0.00000;,
 -2.00000;4.61940;-1.91342;,
 -2.00000;3.53553;-3.53554;,
 -2.00000;1.91341;-4.61940;,
 -8.00000;-1.91342;-4.61940;,
 -8.00000;0.00000;-5.00000;,
 -8.00000;-3.53553;-3.53553;,
 -8.00000;-4.61940;-1.91342;,
 -8.00000;-5.00000;0.00000;,
 -8.00000;-4.61940;1.91342;,
 -8.00000;-3.53553;3.53553;,
 -8.00000;-1.91342;4.61940;,
 -8.00000;-0.00000;5.00000;,
 -8.00000;1.91342;4.61940;,
 -8.00000;3.53553;3.53554;,
 -8.00000;4.61940;1.91342;,
 -8.00000;5.00000;-0.00000;,
 -8.00000;4.61940;-1.91342;,
 -8.00000;3.53553;-3.53554;,
 -8.00000;1.91342;-4.61940;,
 -8.76537;-1.85516;-4.47875;,
 -8.76537;0.00000;-4.84776;,
 -8.76537;-3.42788;-3.42788;,
 -8.76537;-4.47875;-1.85516;,
 -8.76537;-4.84776;0.00000;,
 -8.76537;-4.47875;1.85516;,
 -8.76537;-3.42788;3.42788;,
 -8.76537;-1.85516;4.47875;,
 -8.76537;-0.00000;4.84776;,
 -8.76537;1.85516;4.47875;,
 -8.76537;3.42788;3.42788;,
 -8.76537;4.47875;1.85516;,
 -8.76537;4.84776;-0.00000;,
 -8.76537;4.47875;-1.85516;,
 -8.76537;3.42788;-3.42788;,
 -8.76537;1.85516;-4.47875;,
 -9.41421;-1.68925;-4.07820;,
 -9.41421;0.00000;-4.41421;,
 -9.41421;-3.12132;-3.12132;,
 -9.41421;-4.07820;-1.68925;,
 -9.41421;-4.41421;0.00000;,
 -9.41421;-4.07820;1.68925;,
 -9.41421;-3.12132;3.12132;,
 -9.41421;-1.68925;4.07820;,
 -9.41421;-0.00000;4.41421;,
 -9.41421;1.68925;4.07820;,
 -9.41421;3.12132;3.12132;,
 -9.41421;4.07820;1.68925;,
 -9.41421;4.41421;-0.00000;,
 -9.41421;4.07820;-1.68925;,
 -9.41421;3.12132;-3.12132;,
 -9.41421;1.68924;-4.07820;,
 -9.84776;-1.44094;-3.47875;,
 -9.84776;0.00000;-3.76537;,
 -9.84776;-2.66252;-2.66252;,
 -9.84776;-3.47874;-1.44094;,
 -9.84776;-3.76537;0.00000;,
 -9.84776;-3.47874;1.44094;,
 -9.84776;-2.66252;2.66252;,
 -9.84776;-1.44094;3.47875;,
 -9.84776;-0.00000;3.76537;,
 -9.84776;1.44094;3.47875;,
 -9.84776;2.66252;2.66252;,
 -9.84776;3.47875;1.44094;,
 -9.84776;3.76537;-0.00000;,
 -9.84776;3.47875;-1.44094;,
 -9.84776;2.66252;-2.66252;,
 -9.84776;1.44094;-3.47875;,
 -10.00000;-1.14805;-2.77164;,
 -10.00000;0.00000;-3.00000;,
 -10.00000;-2.12132;-2.12132;,
 -10.00000;-2.77164;-1.14805;,
 -10.00000;-3.00000;0.00000;,
 -10.00000;-2.77164;1.14805;,
 -10.00000;-2.12132;2.12132;,
 -10.00000;-1.14805;2.77164;,
 -10.00000;-0.00000;3.00000;,
 -10.00000;1.14805;2.77164;,
 -10.00000;2.12132;2.12132;,
 -10.00000;2.77164;1.14805;,
 -10.00000;3.00000;-0.00000;,
 -10.00000;2.77164;-1.14805;,
 -10.00000;2.12132;-2.12132;,
 -10.00000;1.14805;-2.77164;,
 -10.00000;0.00000;0.00000;;
 
 176;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,14,13;,
 3;0,15,14;,
 3;0,16,15;,
 3;0,2,16;,
 4;17,18,19,20;,
 4;18,21,22,19;,
 4;21,23,24,22;,
 4;23,5,25,24;,
 4;5,6,26,27;,
 4;6,7,28,26;,
 4;7,8,29,28;,
 4;8,9,30,29;,
 4;9,10,31,30;,
 4;10,11,32,31;,
 4;11,12,33,32;,
 4;12,34,35,33;,
 4;34,36,37,38;,
 4;36,39,40,37;,
 4;39,41,42,40;,
 4;41,17,20,42;,
 4;43,44,45,46;,
 4;44,47,48,45;,
 4;47,49,50,48;,
 4;49,27,51,50;,
 4;27,26,52,51;,
 4;26,28,53,52;,
 4;28,29,54,53;,
 4;29,30,55,54;,
 4;30,31,56,55;,
 4;31,32,57,56;,
 4;32,33,58,57;,
 4;33,35,59,58;,
 4;35,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,43,46,65;,
 4;46,45,66,67;,
 4;45,48,68,66;,
 4;48,50,69,68;,
 4;50,51,70,69;,
 4;51,52,71,70;,
 4;52,53,72,71;,
 4;53,54,73,72;,
 4;54,55,74,73;,
 4;55,56,75,74;,
 4;56,57,76,75;,
 4;57,58,77,76;,
 4;58,59,78,77;,
 4;59,61,79,78;,
 4;61,63,80,79;,
 4;63,65,81,80;,
 4;65,46,67,81;,
 4;67,66,82,83;,
 4;66,68,84,82;,
 4;68,69,85,84;,
 4;69,70,86,85;,
 4;70,71,87,86;,
 4;71,72,88,87;,
 4;72,73,89,88;,
 4;73,74,90,89;,
 4;74,75,91,90;,
 4;75,76,92,91;,
 4;76,77,93,92;,
 4;77,78,94,93;,
 4;78,79,95,94;,
 4;79,80,96,95;,
 4;80,81,97,96;,
 4;81,67,83,97;,
 4;83,82,98,99;,
 4;82,84,100,98;,
 4;84,85,101,100;,
 4;85,86,102,101;,
 4;86,87,103,102;,
 4;87,88,104,103;,
 4;88,89,105,104;,
 4;89,90,106,105;,
 4;90,91,107,106;,
 4;91,92,108,107;,
 4;92,93,109,108;,
 4;93,94,110,109;,
 4;94,95,111,110;,
 4;95,96,112,111;,
 4;96,97,113,112;,
 4;97,83,99,113;,
 4;99,98,114,115;,
 4;98,100,116,114;,
 4;100,101,117,116;,
 4;101,102,118,117;,
 4;102,103,119,118;,
 4;103,104,120,119;,
 4;104,105,121,120;,
 4;105,106,122,121;,
 4;106,107,123,122;,
 4;107,108,124,123;,
 4;108,109,125,124;,
 4;109,110,126,125;,
 4;110,111,127,126;,
 4;111,112,128,127;,
 4;112,113,129,128;,
 4;113,99,115,129;,
 4;115,114,130,131;,
 4;114,116,132,130;,
 4;116,117,133,132;,
 4;117,118,134,133;,
 4;118,119,135,134;,
 4;119,120,136,135;,
 4;120,121,137,136;,
 4;121,122,138,137;,
 4;122,123,139,138;,
 4;123,124,140,139;,
 4;124,125,141,140;,
 4;125,126,142,141;,
 4;126,127,143,142;,
 4;127,128,144,143;,
 4;128,129,145,144;,
 4;129,115,131,145;,
 4;131,130,146,147;,
 4;130,132,148,146;,
 4;132,133,149,148;,
 4;133,134,150,149;,
 4;134,135,151,150;,
 4;135,136,152,151;,
 4;136,137,153,152;,
 4;137,138,154,153;,
 4;138,139,155,154;,
 4;139,140,156,155;,
 4;140,141,157,156;,
 4;141,142,158,157;,
 4;142,143,159,158;,
 4;143,144,160,159;,
 4;144,145,161,160;,
 4;145,131,147,161;,
 4;147,146,162,163;,
 4;146,148,164,162;,
 4;148,149,165,164;,
 4;149,150,166,165;,
 4;150,151,167,166;,
 4;151,152,168,167;,
 4;152,153,169,168;,
 4;153,154,170,169;,
 4;154,155,171,170;,
 4;155,156,172,171;,
 4;156,157,173,172;,
 4;157,158,174,173;,
 4;158,159,175,174;,
 4;159,160,176,175;,
 4;160,161,177,176;,
 4;161,147,163,177;,
 3;163,162,178;,
 3;162,164,178;,
 3;164,165,178;,
 3;165,166,178;,
 3;166,167,178;,
 3;167,168,178;,
 3;168,169,178;,
 3;169,170,178;,
 3;170,171,178;,
 3;171,172,178;,
 3;172,173,178;,
 3;173,174,178;,
 3;174,175,178;,
 3;175,176,178;,
 3;176,177,178;,
 3;177,163,178;;
 
 MeshMaterialList {
  1;
  176;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\arm000.jpg";
   }
  }
 }
 MeshNormals {
  162;
  1.000000;0.000000;0.000000;,
  0.995188;-0.000000;-0.097980;,
  0.995188;-0.037495;-0.090522;,
  0.995188;-0.069282;-0.069282;,
  0.995188;-0.090522;-0.037495;,
  0.995188;-0.097980;0.000000;,
  0.995188;-0.090522;0.037495;,
  0.995188;-0.069282;0.069282;,
  0.995188;-0.037495;0.090522;,
  0.995188;-0.000000;0.097980;,
  0.995188;0.037495;0.090522;,
  0.995188;0.069282;0.069282;,
  0.995188;0.090522;0.037495;,
  0.995188;0.097980;0.000000;,
  0.995188;0.090522;-0.037495;,
  0.995188;0.069282;-0.069282;,
  0.995188;0.037495;-0.090522;,
  0.924082;-0.000000;-0.382195;,
  0.924082;-0.146260;-0.353102;,
  0.924082;-0.270252;-0.270252;,
  0.924082;-0.353102;-0.146260;,
  0.924082;-0.382195;0.000000;,
  0.924082;-0.353102;0.146260;,
  0.924082;-0.270253;0.270253;,
  0.924082;-0.146260;0.353102;,
  0.924082;-0.000000;0.382195;,
  0.924082;0.146260;0.353102;,
  0.924082;0.270252;0.270253;,
  0.924082;0.353102;0.146260;,
  0.924082;0.382195;0.000000;,
  0.924082;0.353102;-0.146260;,
  0.924082;0.270252;-0.270253;,
  0.924082;0.146260;-0.353102;,
  0.707629;-0.000000;-0.706585;,
  0.707629;-0.270398;-0.652799;,
  0.707629;-0.499631;-0.499631;,
  0.707629;-0.652799;-0.270398;,
  0.707628;-0.706585;0.000000;,
  0.707628;-0.652799;0.270398;,
  0.707629;-0.499631;0.499631;,
  0.707629;-0.270398;0.652799;,
  0.707629;-0.000000;0.706585;,
  0.707629;0.270398;0.652799;,
  0.707629;0.499630;0.499631;,
  0.707629;0.652799;0.270398;,
  0.707629;0.706584;0.000000;,
  0.707629;0.652799;-0.270398;,
  0.707629;0.499630;-0.499631;,
  0.707629;0.270398;-0.652799;,
  0.383160;-0.000000;-0.923682;,
  0.383160;-0.353478;-0.853371;,
  0.383160;-0.653142;-0.653142;,
  0.383159;-0.853371;-0.353478;,
  0.383159;-0.923682;0.000000;,
  0.383159;-0.853371;0.353478;,
  0.383160;-0.653142;0.653142;,
  0.383160;-0.353478;0.853371;,
  0.383160;-0.000000;0.923682;,
  0.383160;0.353478;0.853371;,
  0.383160;0.653142;0.653142;,
  0.383160;0.853371;0.353478;,
  0.383160;0.923682;-0.000000;,
  0.383160;0.853371;-0.353478;,
  0.383160;0.653142;-0.653142;,
  0.383160;0.353478;-0.853371;,
  0.098053;-0.000000;-0.995181;,
  0.098053;-0.380839;-0.919428;,
  0.098052;-0.703699;-0.703699;,
  0.098053;-0.919428;-0.380839;,
  0.098053;-0.995181;0.000000;,
  0.098053;-0.919428;0.380839;,
  0.098053;-0.703699;0.703699;,
  0.098053;-0.380839;0.919428;,
  0.098053;-0.000000;0.995181;,
  0.098053;0.380839;0.919428;,
  0.098053;0.703699;0.703700;,
  0.098053;0.919427;0.380839;,
  0.098053;0.995181;0.000000;,
  0.098053;0.919427;-0.380840;,
  0.098053;0.703699;-0.703700;,
  0.098053;0.380839;-0.919428;,
  -0.098053;-0.000000;-0.995181;,
  -0.098052;-0.380839;-0.919428;,
  -0.098052;-0.703699;-0.703699;,
  -0.098052;-0.919428;-0.380839;,
  -0.098053;-0.995181;0.000000;,
  -0.098052;-0.919428;0.380839;,
  -0.098052;-0.703699;0.703699;,
  -0.098052;-0.380839;0.919428;,
  -0.098052;-0.000000;0.995181;,
  -0.098052;0.380839;0.919428;,
  -0.098052;0.703699;0.703700;,
  -0.098053;0.919427;0.380839;,
  -0.098053;0.995181;-0.000000;,
  -0.098053;0.919427;-0.380840;,
  -0.098052;0.703699;-0.703700;,
  -0.098052;0.380839;-0.919428;,
  -0.383160;-0.000000;-0.923682;,
  -0.383160;-0.353478;-0.853371;,
  -0.383160;-0.653142;-0.653142;,
  -0.383160;-0.853371;-0.353478;,
  -0.383160;-0.923682;0.000000;,
  -0.383160;-0.853371;0.353478;,
  -0.383160;-0.653142;0.653142;,
  -0.383160;-0.353478;0.853371;,
  -0.383160;-0.000000;0.923682;,
  -0.383160;0.353478;0.853371;,
  -0.383160;0.653142;0.653142;,
  -0.383159;0.853371;0.353478;,
  -0.383159;0.923682;-0.000000;,
  -0.383159;0.853371;-0.353478;,
  -0.383160;0.653142;-0.653142;,
  -0.383160;0.353478;-0.853371;,
  -0.707629;-0.000000;-0.706584;,
  -0.707629;-0.270398;-0.652799;,
  -0.707629;-0.499631;-0.499631;,
  -0.707629;-0.652799;-0.270398;,
  -0.707629;-0.706584;0.000000;,
  -0.707629;-0.652799;0.270398;,
  -0.707629;-0.499631;0.499631;,
  -0.707629;-0.270398;0.652799;,
  -0.707629;-0.000000;0.706584;,
  -0.707629;0.270398;0.652799;,
  -0.707629;0.499631;0.499631;,
  -0.707629;0.652799;0.270398;,
  -0.707628;0.706585;0.000000;,
  -0.707629;0.652799;-0.270398;,
  -0.707629;0.499631;-0.499631;,
  -0.707629;0.270398;-0.652799;,
  -0.924082;-0.000000;-0.382195;,
  -0.924082;-0.146260;-0.353102;,
  -0.924082;-0.270253;-0.270252;,
  -0.924082;-0.353102;-0.146260;,
  -0.924082;-0.382195;0.000000;,
  -0.924082;-0.353102;0.146260;,
  -0.924082;-0.270253;0.270252;,
  -0.924082;-0.146260;0.353102;,
  -0.924082;-0.000000;0.382195;,
  -0.924082;0.146260;0.353102;,
  -0.924082;0.270252;0.270253;,
  -0.924082;0.353102;0.146260;,
  -0.924082;0.382195;0.000000;,
  -0.924082;0.353102;-0.146260;,
  -0.924082;0.270252;-0.270253;,
  -0.924082;0.146260;-0.353102;,
  -0.995188;-0.000000;-0.097980;,
  -0.995188;-0.037495;-0.090522;,
  -0.995188;-0.069282;-0.069282;,
  -0.995188;-0.090522;-0.037495;,
  -0.995188;-0.097980;0.000000;,
  -0.995188;-0.090522;0.037495;,
  -0.995188;-0.069282;0.069282;,
  -0.995188;-0.037495;0.090522;,
  -0.995188;-0.000000;0.097980;,
  -0.995188;0.037495;0.090522;,
  -0.995188;0.069282;0.069282;,
  -0.995188;0.090522;0.037495;,
  -0.995188;0.097980;0.000000;,
  -0.995188;0.090522;-0.037495;,
  -0.995188;0.069282;-0.069282;,
  -0.995188;0.037495;-0.090522;,
  -1.000000;0.000000;0.000000;;
  176;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,1,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,80,96,95;,
  4;80,65,81,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,96,112,111;,
  4;96,81,97,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,112,128,127;,
  4;112,97,113,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,128,144,143;,
  4;128,113,129,144;,
  4;129,130,146,145;,
  4;130,131,147,146;,
  4;131,132,148,147;,
  4;132,133,149,148;,
  4;133,134,150,149;,
  4;134,135,151,150;,
  4;135,136,152,151;,
  4;136,137,153,152;,
  4;137,138,154,153;,
  4;138,139,155,154;,
  4;139,140,156,155;,
  4;140,141,157,156;,
  4;141,142,158,157;,
  4;142,143,159,158;,
  4;143,144,160,159;,
  4;144,129,145,160;,
  3;145,146,161;,
  3;146,147,161;,
  3;147,148,161;,
  3;148,149,161;,
  3;149,150,161;,
  3;150,151,161;,
  3;151,152,161;,
  3;152,153,161;,
  3;153,154,161;,
  3;154,155,161;,
  3;155,156,161;,
  3;156,157,161;,
  3;157,158,161;,
  3;158,159,161;,
  3;159,160,161;,
  3;160,145,161;;
 }
 MeshTextureCoords {
  179;
  0.750000;0.500000;,
  1.000000;0.614805;,
  1.000000;0.500000;,
  1.000000;0.712132;,
  1.000000;0.777164;,
  0.500000;0.800000;,
  0.500000;0.777164;,
  0.500000;0.712132;,
  0.500000;0.614805;,
  0.500000;0.500000;,
  0.500000;0.385195;,
  0.500000;0.287868;,
  0.500000;0.222836;,
  1.000000;0.200000;,
  1.000000;0.222836;,
  1.000000;0.287868;,
  1.000000;0.385195;,
  0.000000;0.500000;,
  0.000000;0.614805;,
  -0.006961;0.644094;,
  -0.006431;0.500000;,
  0.000000;0.712132;,
  -0.009090;0.766252;,
  0.000000;0.777164;,
  -0.016753;0.847875;,
  -0.250000;0.876537;,
  0.516753;0.847875;,
  0.750000;0.876537;,
  0.509090;0.766252;,
  0.506961;0.644094;,
  0.506431;0.500000;,
  0.506961;0.355906;,
  0.509090;0.233748;,
  0.516753;0.152126;,
  0.000000;0.200000;,
  0.750000;0.123463;,
  0.000000;0.222836;,
  -0.016753;0.152126;,
  -0.250000;0.123463;,
  0.000000;0.287868;,
  -0.009090;0.233748;,
  0.000000;0.385195;,
  -0.006961;0.355906;,
  0.993569;0.500000;,
  0.993039;0.644094;,
  0.977295;0.668925;,
  0.979002;0.500000;,
  0.990910;0.766252;,
  0.970474;0.812132;,
  0.983247;0.847875;,
  0.946874;0.907820;,
  0.750000;0.941421;,
  0.553126;0.907820;,
  0.529526;0.812132;,
  0.522705;0.668925;,
  0.520998;0.500000;,
  0.522705;0.331075;,
  0.529526;0.187868;,
  0.553126;0.092180;,
  0.750000;0.058579;,
  0.983247;0.152126;,
  0.946874;0.092180;,
  0.990910;0.233748;,
  0.970474;0.187868;,
  0.993039;0.355906;,
  0.977295;0.331076;,
  0.957190;0.685516;,
  0.960310;0.500000;,
  0.944979;0.842788;,
  0.906543;0.947875;,
  0.750000;0.984776;,
  0.593457;0.947875;,
  0.555021;0.842788;,
  0.542810;0.685516;,
  0.539690;0.500000;,
  0.542810;0.314484;,
  0.555021;0.157212;,
  0.593456;0.052125;,
  0.750000;0.015224;,
  0.906544;0.052125;,
  0.944979;0.157212;,
  0.957190;0.314485;,
  0.934971;0.691342;,
  0.939441;0.500000;,
  0.918066;0.853553;,
  0.871479;0.961940;,
  0.750000;1.000000;,
  0.628521;0.961940;,
  0.581934;0.853553;,
  0.565029;0.691342;,
  0.560560;0.500000;,
  0.565029;0.308658;,
  0.581934;0.146447;,
  0.628521;0.038060;,
  0.750000;0.000000;,
  0.871479;0.038060;,
  0.918066;0.146447;,
  0.934971;0.308659;,
  0.833342;0.691342;,
  0.838904;0.500000;,
  0.816230;0.853553;,
  0.787364;0.961940;,
  0.750000;1.000000;,
  0.712636;0.961940;,
  0.683770;0.853553;,
  0.666658;0.691342;,
  0.661096;0.500000;,
  0.666658;0.308658;,
  0.683770;0.146447;,
  0.712636;0.038060;,
  0.750000;0.000000;,
  0.787364;0.038060;,
  0.816230;0.146447;,
  0.833342;0.308658;,
  0.825181;0.685516;,
  0.830403;0.500000;,
  0.809331;0.842788;,
  0.783195;0.947875;,
  0.750000;0.984776;,
  0.716805;0.947875;,
  0.690669;0.842788;,
  0.674819;0.685516;,
  0.669597;0.500000;,
  0.674819;0.314484;,
  0.690669;0.157212;,
  0.716805;0.052125;,
  0.750000;0.015224;,
  0.783195;0.052125;,
  0.809331;0.157212;,
  0.825181;0.314484;,
  0.815061;0.668925;,
  0.819781;0.500000;,
  0.800953;0.812132;,
  0.778257;0.907820;,
  0.750000;0.941421;,
  0.721743;0.907820;,
  0.699047;0.812132;,
  0.684939;0.668925;,
  0.680219;0.500000;,
  0.684939;0.331075;,
  0.699047;0.187868;,
  0.721743;0.092180;,
  0.750000;0.058579;,
  0.778257;0.092180;,
  0.800953;0.187868;,
  0.815061;0.331076;,
  0.804044;0.644094;,
  0.808124;0.500000;,
  0.792026;0.766252;,
  0.773124;0.847875;,
  0.750000;0.876537;,
  0.726876;0.847875;,
  0.707974;0.766252;,
  0.695956;0.644094;,
  0.691876;0.500000;,
  0.695956;0.355906;,
  0.707974;0.233748;,
  0.726876;0.152125;,
  0.750000;0.123463;,
  0.773124;0.152125;,
  0.792026;0.233748;,
  0.804044;0.355906;,
  0.793032;0.614805;,
  0.796387;0.500000;,
  0.783269;0.712132;,
  0.768192;0.777164;,
  0.750000;0.800000;,
  0.731808;0.777164;,
  0.716731;0.712132;,
  0.706968;0.614805;,
  0.703613;0.500000;,
  0.706968;0.385195;,
  0.716731;0.287868;,
  0.731808;0.222836;,
  0.750000;0.200000;,
  0.768192;0.222836;,
  0.783269;0.287868;,
  0.793032;0.385195;,
  0.750000;0.500000;;
 }
}
