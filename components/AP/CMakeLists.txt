idf_component_register(
  SRCS
  wifi_ap_ctrl.c
  INCLUDE_DIRS
  include
  REQUIRES
  esp_wifi
  nvs_flash)
