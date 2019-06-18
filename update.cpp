extern "C" {
#include "update.h"
}

#include <codecvt>
#include <locale>

#include "JSON.h"

std::string wstring_to_string(const std::wstring& wstring) {
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;
  return converter.to_bytes(wstring);
}

int update(ktxTexture* texture, char* data_string) {
  JSONValue* data = JSON::Parse(data_string);
  if (!data) {
    return -1;
  }

  for (std::wstring& key : data->ObjectKeys()) {
    auto value_object = data->Child(key.c_str());
    if (value_object->IsNumber()) {
      auto value = (uint32_t) value_object->AsNumber();
      ktxHashList_AddKVPair(&texture->kvDataHead,
                            wstring_to_string(key).c_str(),
                            sizeof(value), &value);
    }
  }
  return 0;
}
