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
template<class T>
void writeArray(ktxTexture* texture,
                const char* key_string,
                const JSONArray& array) {
  size_t size = array.size() * sizeof(T);
  auto values = (T*) malloc(size);
  auto writePtr = values;
  for (auto object : array) {
    *writePtr++ = (T) object->AsNumber();
  }
  ktxHashList_AddKVPair(&texture->kvDataHead,
                        key_string,
                        (unsigned int) size,
                        values);
  free(values);
}

int update(ktxTexture* texture, char* data_string, int width) {
  JSONValue* data = JSON::Parse(data_string);
  if (!data) {
    return -1;
  }
  for (std::wstring& key_wstring : data->ObjectKeys()) {
    auto value_object = data->Child(key_wstring.c_str());
    const char* key_string = wstring_to_string(key_wstring).c_str();
    if (value_object->IsNumber()) {
      if (width == 8) {
        auto value = (uint8_t) value_object->AsNumber();
        ktxHashList_AddKVPair(&texture->kvDataHead,
                              key_string,
                              sizeof(value),
                              &value);
      } else if (width == 16) {
        auto value = (uint16_t) value_object->AsNumber();
        ktxHashList_AddKVPair(&texture->kvDataHead,
                              key_string,
                              sizeof(value),
                              &value);
      } else if (width == 32) {
        auto value = (uint32_t) value_object->AsNumber();
        ktxHashList_AddKVPair(&texture->kvDataHead,
                              key_string,
                              sizeof(value),
                              &value);
      }
    } else if (value_object->IsArray()) {
      const JSONArray& array = value_object->AsArray();
      if (width == 8) {
        writeArray<uint8_t>(texture, key_string, array);
      } else if (width == 16) {
        writeArray<uint16_t>(texture, key_string, array);
      } else if (width == 32) {
        writeArray<uint32_t>(texture, key_string, array);
      }
    }
  }
  return 0;
}