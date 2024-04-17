void chatgpt(){
  String result;
//  String q = "test";
//  Serial.println(q);
  if(!chatgpt_Q.isEmpty()) {
    chatgpt_Q.trim();
  }
  if (chat_gpt.simple_message("gpt-3.5-turbo-0301", "user", chatgpt_Q, result)) {
    Serial.println("===OK===");
    Serial.println(result);
    chatgpt_R = result;
  } else {
    Serial.println("===ERROR===");
    Serial.println(result);
    chatgpt_R = result;
  }
}
