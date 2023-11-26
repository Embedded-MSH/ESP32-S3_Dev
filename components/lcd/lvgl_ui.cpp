
#include "esp_log.h"
#include "lvgl.h"

#include <string>

static const char* TAG = "LCD Ctrl";
#ifdef __cplusplus
extern "C"
{
#endif
    void lv_example_grid_x(lv_disp_t* disp)
    {
        // static int16_t col_dsc[] = { 40, 40, 40, LV_GRID_TEMPLATE_LAST };
        // static int16_t row_dsc[] = { 20, 20, 20, LV_GRID_TEMPLATE_LAST };

        static int16_t col_dsc[] = { 40, LV_GRID_TEMPLATE_LAST };
        static int16_t row_dsc[] = { 20, LV_GRID_TEMPLATE_LAST };
        /*Create a container with grid*/

        lv_obj_t* scr = lv_disp_get_scr_act(disp);
        lv_obj_t* cont = lv_obj_create(scr);
        lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
        lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
        lv_obj_set_size(cont, 170, 110);
        lv_obj_center(cont);
        lv_obj_set_layout(cont, LV_LAYOUT_GRID);


        uint32_t i;
        for (i = 0; i < 1; i++) {
            uint8_t col = i % 3;
            uint8_t row = i / 3;

            ESP_LOGI(TAG, "col = %d, row = %d", col, row);

            auto obj = lv_label_create(cont);

            lv_label_set_text_fmt(obj, "initializing...");
            /*Stretch the cell horizontally and vertically too
             *Set span to 1 to make the cell 1 column/row sized*/
            lv_obj_set_grid_cell(obj,
                                 LV_GRID_ALIGN_STRETCH,
                                 col,
                                 1,
                                 LV_GRID_ALIGN_STRETCH,
                                 row,
                                 1);
        }
    }

#ifdef __cplusplus
}
#endif
