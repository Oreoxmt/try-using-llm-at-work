# SHA256('try-using-llm-at-work:service.capnp')[:16]
@0xe16ebe1b28ad9012;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("muton::playground::llm::proto");

interface Tokenizer {
  struct Tokens {
    size @0 :UInt32;
    tokenId @1 :List(Int32);
    tokenPos @2 :List(UInt32);
    tokenSize @3 :List(UInt32);
  }
  tokenize @0 (text: Text) -> (tokens :Tokens);
}
