/*BEGIN_LEGAL 
  Intel Open Source License 

  Copyright (c) 2002-2014 Intel Corporation. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.  Redistributions
  in binary form must reproduce the above copyright notice, this list of
  conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.  Neither the name of
  the Intel Corporation nor the names of its contributors may be used to
  endorse or promote products derived from this software without
  specific prior written permission.
 
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
  ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  END_LEGAL */
/*
 *  This file contains an ISA-portable PIN tool for tracing memory accesses.
 */

#include <stdio.h>
#include "pin.H"

#include"wrapper.h"
#include"cache.h"
#include<string>
#include<sstream>
#include<fstream>
#include<cstdint>


FILE * trace;
FILE * itrace;
Wrapper* w;
int numCaches;

// Print a memory read record
VOID RecordMemRead(VOID * ip, VOID * addr)
{
  //fprintf(trace,"%p: R %p\n", ip, addr);
  w->read((uint64_t) addr);
}

// Print a memory write record
VOID RecordMemWrite(VOID * ip, VOID * addr)
{
  //fprintf(trace,"%p: W %p\n", ip, addr);
  w->write((uint64_t) addr);

}

VOID ReadInst(void* addr){
  w->read((uint64_t)addr);
  //cout << "read: " << addr << endl;
}

// Is called for every instruction and instruments reads and writes
VOID Instruction(INS ins, VOID *v)
{
  // Instruments memory accesses using a predicated call, i.e.
  // the instrumentation is called iff the instruction will actually be executed.
  //
  // On the IA-32 and Intel(R) 64 architectures conditional moves and REP 
  // prefixed instructions appear as predicated instructions in Pin.
  
  //w->read(INS_Address(ins)); // reading the instruction (from our cache)
  
  //cout << INS_Address(ins) << endl;
  //ADDRINT addr = INS_Address(ins);
  INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)ReadInst, IARG_INST_PTR, IARG_END);
  
  UINT32 memOperands = INS_MemoryOperandCount(ins);
  
  // Iterate over each memory operand of the instruction.
  for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
      if (INS_MemoryOperandIsRead(ins, memOp))
        {
	  INS_InsertPredicatedCall(
				   ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,
				   IARG_INST_PTR,
				   IARG_MEMORYOP_EA, memOp,
				   IARG_END);
        }
      // Note that in some architectures a single memory operand can be 
      // both read and written (for instance incl (%eax) on IA-32)
      // In that case we instrument it once for read and once for write.
      if (INS_MemoryOperandIsWritten(ins, memOp))
        {
	  INS_InsertPredicatedCall(
				   ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite,
				   IARG_INST_PTR,
				   IARG_MEMORYOP_EA, memOp,
				   IARG_END);
        }
    }
}

VOID Fini(INT32 code, VOID *v)
{
  fprintf(trace, "#eof\n");
  fclose(trace);
  for(int i = 0; i < numCaches; i++){
    
    cout << w->cacheArray[i].readHits 
	 << ", " << w->cacheArray[i].readMisses 
	 << ", " << w->cacheArray[i].writeHits 
	 << ", " << w->cacheArray[i].writeMisses
	 << ", " << w->cacheArray[i].hits
	 << ", " << w->cacheArray[i].misses_non_dirty
	 << ", " << w->cacheArray[i].misses_dirty	 
	 << endl;

    /*
    cout << endl;
    cout << "L" << i+1 << ": read hits: " << w->cacheArray[i].readHits << endl;
    cout << "L" << i+1 << ": read misses: " << w->cacheArray[i].readMisses << endl;
    cout << "L" << i+1 << ": write hits: " << w->cacheArray[i].writeHits << endl;
    cout << "L" << i+1 << ": write misses: " << w->cacheArray[i].writeMisses << endl;
    cout << "-----------------------------------\n";
    */
  }
  
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
   
INT32 Usage()
{
  PIN_ERROR( "This Pintool prints a trace of memory addresses\n" 
	     + KNOB_BASE::StringKnobSummary() + "\n");
  return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
  if (PIN_Init(argc, argv)) return Usage();
    
  trace = fopen("pinatrace.out2", "w");
  itrace = fopen("itr.out", "w");
  
  // read config.txt
  string line;
  ifstream f("config.txt");
  getline(f, line);
  stringstream ss(line);
  string temp;
  
  ss >> temp >> temp >> numCaches;

  w = new Wrapper(numCaches);

  int i;
  for(i = 0; i < numCaches; i++){
    getline(f, line); // blank line
    
    getline(f, line); // [Level i]
    
    getline(f, line); // Size = ??KB
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    string sz_str = temp.substr(0, temp.length() - 2);
    int size = stoi(sz_str);
    
    getline(f, line); // Associativity = ??
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp;
    int asso;
    ss >> asso;
    
    getline(f, line); // Block_size = ??bytes
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    sz_str = temp.substr(0, temp.length() - 5);
    int blockSize = stoi(sz_str);
       
    getline(f, line); // Hit_Latency = ?? // ignore
    
    getline(f, line); // Replacement_Policy = LRU
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    //    cerr << "replacement policy: " << temp << endl;
    int replacementPolicy;
    if(temp.compare("LRU") == 0){
      replacementPolicy = 0;
      
    }else if(temp.compare("LFU") == 0){
      replacementPolicy = 1;
    }else{
      replacementPolicy = 2;
    }
    
    w->cacheArray[i] = Cache(i, w, size, asso, blockSize, replacementPolicy);
    
  }
  f.close();
  
   

  INS_AddInstrumentFunction(Instruction, 0);
  PIN_AddFiniFunction(Fini, 0);
    
  // Never returns
  PIN_StartProgram();
    
  return 0;
}
