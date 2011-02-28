// Copyright 2008 Google Inc. All Rights Reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Test printing of cyclic arrays.

var a1 = [1,2];
assertEquals("1,2", a1.toString());
assertEquals("1,2", a1.toLocaleString());
assertEquals("1,2", a1.join());
a1.push(a1);
assertEquals("1,2,", a1.toString());
assertEquals("1,2,", a1.toLocaleString());
assertEquals("1,2,", a1.join());
a1.push(1);
assertEquals("1,2,,1", a1.toString());
assertEquals("1,2,,1", a1.toLocaleString());
assertEquals("1,2,,1", a1.join());
a1.push(a1);
assertEquals("1,2,,1,", a1.toString());
assertEquals("1,2,,1,", a1.toLocaleString());
assertEquals("1,2,,1,", a1.join());

a1 = [1,2];
var a2 = [3,4];
a1.push(a2);
a1.push(a2);
assertEquals("1,2,3,4,3,4", a1.toString());
assertEquals("1,2,3,4,3,4", a1.toLocaleString());
assertEquals("1,2,3,4,3,4", a1.join());
a2.push(a1);
assertEquals("1,2,3,4,,3,4,", a1.toString());
assertEquals("1,2,3,4,,3,4,", a1.toLocaleString());
assertEquals("1,2,3,4,,3,4,", a1.join());

a1 = [];
a2 = [a1];
a1.push(a2);
assertEquals("", a1.toString());
assertEquals("", a1.toLocaleString());
assertEquals("", a1.join());

