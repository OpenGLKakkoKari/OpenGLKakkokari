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
 96;
 -300.00000;224.99551;-37.49541;,
 -150.00000;224.99551;-37.49541;,
 -150.00000;150.00458;-37.50000;,
 -300.00000;150.00458;-37.50000;,
 -150.00000;224.99551;37.49541;,
 -150.00000;150.00458;74.99083;,
 -150.00000;150.00458;-37.50000;,
 -150.00000;224.99551;-37.49541;,
 -150.00000;224.99551;37.49541;,
 -300.00000;224.99551;37.49541;,
 -300.00000;150.00458;74.99083;,
 -150.00000;150.00458;74.99083;,
 -300.00000;224.99551;37.49541;,
 -300.00000;224.99551;-37.49541;,
 -300.00000;150.00458;-37.50000;,
 -300.00000;150.00458;74.99083;,
 -150.00000;224.99551;-37.49541;,
 -300.00000;224.99551;-37.49541;,
 -300.00000;150.00458;-37.50000;,
 -150.00000;150.00458;-37.50000;,
 0.00000;224.99551;-37.49541;,
 0.00000;150.00458;-37.50000;,
 0.00000;224.99551;37.49541;,
 0.00000;150.00458;74.99083;,
 0.00000;150.00458;-37.50000;,
 0.00000;224.99551;-37.49541;,
 0.00000;224.99551;37.49541;,
 0.00000;150.00458;74.99083;,
 0.00000;224.99551;-37.49541;,
 -150.00000;224.99551;-37.49541;,
 -150.00000;150.00458;-37.50000;,
 0.00000;150.00458;-37.50000;,
 -150.00000;0.00000;-37.50000;,
 -300.00000;0.00000;-37.50000;,
 -150.00000;150.00458;74.99083;,
 -150.00000;0.00000;150.00000;,
 -150.00000;0.00000;-37.50000;,
 -150.00000;150.00458;74.99083;,
 -300.00000;150.00458;74.99083;,
 -300.00000;0.00000;150.00000;,
 -150.00000;0.00000;150.00000;,
 -300.00000;150.00458;74.99083;,
 -300.00000;150.00458;-37.50000;,
 -300.00000;0.00000;-37.50000;,
 -300.00000;0.00000;150.00000;,
 -300.00000;0.00000;-37.50000;,
 -150.00000;0.00000;-37.50000;,
 0.00000;0.00000;-37.50000;,
 0.00000;150.00458;74.99083;,
 0.00000;0.00000;150.00000;,
 0.00000;0.00000;-37.50000;,
 0.00000;150.00458;-37.50000;,
 0.00000;150.00458;74.99083;,
 0.00000;0.00000;150.00000;,
 -150.00000;0.00000;-37.50000;,
 0.00000;0.00000;-37.50000;,
 150.00000;224.99551;-37.49541;,
 150.00000;150.00458;-37.50000;,
 150.00000;224.99551;37.49541;,
 150.00000;150.00458;74.99083;,
 150.00000;150.00458;-37.50000;,
 150.00000;224.99551;-37.49541;,
 150.00000;224.99551;37.49541;,
 150.00000;150.00458;74.99083;,
 150.00000;224.99551;-37.49541;,
 0.00000;224.99551;-37.49541;,
 150.00000;150.00458;-37.50000;,
 300.00000;224.99551;-37.49541;,
 300.00000;150.00458;-37.50000;,
 300.00000;224.99551;37.49541;,
 300.00000;150.00458;74.99083;,
 300.00000;150.00458;-37.50000;,
 300.00000;224.99551;-37.49541;,
 300.00000;224.99551;37.49541;,
 300.00000;150.00458;74.99083;,
 300.00000;224.99551;-37.49541;,
 150.00000;224.99551;-37.49541;,
 150.00000;150.00458;-37.50000;,
 300.00000;150.00458;-37.50000;,
 150.00000;0.00000;-37.50000;,
 150.00000;150.00458;74.99083;,
 150.00000;0.00000;150.00000;,
 150.00000;0.00000;-37.50000;,
 150.00000;150.00458;74.99083;,
 150.00000;0.00000;150.00000;,
 0.00000;0.00000;-37.50000;,
 150.00000;0.00000;-37.50000;,
 300.00000;0.00000;-37.50000;,
 300.00000;150.00458;74.99083;,
 300.00000;0.00000;150.00000;,
 300.00000;0.00000;-37.50000;,
 300.00000;150.00458;-37.50000;,
 300.00000;150.00458;74.99083;,
 300.00000;0.00000;150.00000;,
 150.00000;0.00000;-37.50000;,
 300.00000;0.00000;-37.50000;;
 
 96;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;8,9,10;,
 3;8,10,11;,
 3;12,13,14;,
 3;12,14,15;,
 3;12,4,16;,
 3;12,16,17;,
 3;18,19,5;,
 3;18,5,15;,
 3;7,20,21;,
 3;7,21,6;,
 3;22,23,24;,
 3;22,24,25;,
 3;26,4,5;,
 3;26,5,27;,
 3;8,1,2;,
 3;8,2,11;,
 3;8,22,28;,
 3;8,28,29;,
 3;30,31,23;,
 3;30,23,11;,
 3;18,19,32;,
 3;18,32,33;,
 3;34,35,36;,
 3;34,36,30;,
 3;37,38,39;,
 3;37,39,40;,
 3;41,42,43;,
 3;41,43,44;,
 3;41,34,2;,
 3;41,2,3;,
 3;45,46,35;,
 3;45,35,44;,
 3;30,31,47;,
 3;30,47,36;,
 3;48,49,50;,
 3;48,50,51;,
 3;52,34,35;,
 3;52,35,53;,
 3;37,19,32;,
 3;37,32,40;,
 3;37,48,21;,
 3;37,21,6;,
 3;54,55,49;,
 3;54,49,40;,
 3;25,56,57;,
 3;25,57,24;,
 3;58,59,60;,
 3;58,60,61;,
 3;62,22,23;,
 3;62,23,63;,
 3;26,20,21;,
 3;26,21,27;,
 3;26,58,64;,
 3;26,64,65;,
 3;51,66,59;,
 3;51,59,27;,
 3;61,67,68;,
 3;61,68,60;,
 3;69,70,71;,
 3;69,71,72;,
 3;73,58,59;,
 3;73,59,74;,
 3;62,56,57;,
 3;62,57,63;,
 3;62,69,75;,
 3;62,75,76;,
 3;77,78,70;,
 3;77,70,63;,
 3;51,66,79;,
 3;51,79,50;,
 3;80,81,82;,
 3;80,82,77;,
 3;83,48,49;,
 3;83,49,84;,
 3;52,31,47;,
 3;52,47,53;,
 3;52,80,57;,
 3;52,57,24;,
 3;85,86,81;,
 3;85,81,53;,
 3;77,78,87;,
 3;77,87,82;,
 3;88,89,90;,
 3;88,90,91;,
 3;92,80,81;,
 3;92,81,93;,
 3;83,66,79;,
 3;83,79,84;,
 3;83,88,68;,
 3;83,68,60;,
 3;94,95,89;,
 3;94,89,84;;
 
 MeshMaterialList {
  1;
  96;
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
    "data/TEXTURE/Field/stone.jpg";
   }
  }
 }
 MeshNormals {
  16;
  0.000000;0.000061;-1.000000;,
  0.000000;0.000020;-1.000000;,
  0.000000;0.000031;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.447213;0.894428;,
  0.000000;0.447224;0.894422;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.447246;0.894411;,
  0.000000;0.000041;-1.000000;,
  0.000000;0.447213;0.894427;,
  0.000000;0.447230;0.894419;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.447213;0.894427;,
  0.000000;0.447235;0.894416;;
  96;
  3;0,0,2;,
  3;0,2,1;,
  3;3,3,3;,
  3;3,3,3;,
  3;9,4,5;,
  3;9,5,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;0,0,2;,
  3;0,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;9,9,10;,
  3;9,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;1,2,6;,
  3;1,6,6;,
  3;3,3,3;,
  3;3,3,3;,
  3;10,5,7;,
  3;10,7,7;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;2,2,6;,
  3;2,6,6;,
  3;3,3,3;,
  3;3,3,3;,
  3;10,10,7;,
  3;10,7,7;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;0,0,2;,
  3;0,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;9,9,10;,
  3;9,10,10;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;0,0,8;,
  3;0,8,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;14,9,10;,
  3;14,10,15;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;2,2,6;,
  3;2,6,6;,
  3;3,3,3;,
  3;3,3,3;,
  3;10,10,7;,
  3;10,7,7;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;,
  3;2,8,6;,
  3;2,6,6;,
  3;3,3,3;,
  3;3,3,3;,
  3;15,10,7;,
  3;15,7,7;,
  3;11,11,11;,
  3;11,11,11;,
  3;12,12,12;,
  3;12,12,12;,
  3;13,13,13;,
  3;13,13,13;;
 }
 MeshTextureCoords {
  96;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
