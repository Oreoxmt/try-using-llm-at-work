#include "catch2/catch_test_macros.hpp"

#include "config/Config.h"
#include "llama/LlamaContext.h"
#include "llama/LlamaModel.h"
#include "llama/LlamaParams.h"
#include "llama/LlamaScope.h"
#include "llama/LlamaTokenizer.h"

TEST_CASE("The model maintains (feed, eval, and predict) the context correctly", "[llama][context]") {
  // Build the model (llama-2-7b.Q4_0.gguf).
  // The predict.temperature is 0.0.
  auto config = muton::playground::llm::Config::Read();
  muton::playground::llm::LlamaScope scope(true);
  muton::playground::llm::LlamaParams params(config->getParams());
  muton::playground::llm::LlamaModel model(config->getModel().cStr(), params);
  // Build the tokenizer and the context.
  muton::playground::llm::LlamaTokenizer tokenizer(model);
  muton::playground::llm::LlamaContext context(params, model);
  auto vocab = model.GetVocabulary();
  auto tokens = tokenizer.Tokenize(" When life gives you lemons,");
  REQUIRE(context.FeedBos() == true);              // Indicates the beginning of a sentence.
  REQUIRE(context.Feed(tokens.token_id) == true);  // Feed all tokens.
  REQUIRE(context.Eval(config->getEval()) == true);
  std::vector<std::string> prediction{" make", " le", "mon", "ade", "."};
  for (const auto predict_token : prediction) {
    auto next_token = context.Predict(config->getPredict());
    REQUIRE(context.Feed(next_token) == true);
    REQUIRE(context.Eval(config->getEval()) == true);
    REQUIRE(vocab.pieces[next_token] == predict_token);
  }
}
