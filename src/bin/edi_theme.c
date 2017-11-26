#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "Edi.h"
#include "edi_theme.h"
#include "edi_config.h"
#include "edi_private.h"

static Eina_List *_edi_themes = NULL;

void
edi_theme_theme_set(Evas_Object *obj, const char *name)
{
   Eina_List *l;
   Edi_Theme *theme;

   if (!name || !strcasecmp(name, "default"))
     return;

   edi_theme_themes_get();

   EINA_LIST_FOREACH(_edi_themes, l, theme)
     {
        if (strcmp(theme->name, name))
          continue;

        elm_layout_file_set(obj, theme->path, "elm/code/layout/default");
     }
}

Eina_List *
edi_theme_themes_get(void)
{
   Eina_List *files;
   char *directory, *file, *name;
   Edi_Theme *theme;

   if (_edi_themes) return _edi_themes;

   directory = PACKAGE_DATA_DIR "/themes";

   theme = malloc(sizeof(Edi_Theme));
   theme->name = strdup("default");
   theme->path = NULL;
   _edi_themes = eina_list_append(_edi_themes, theme); 

   files = ecore_file_ls(directory);
   EINA_LIST_FREE(files, file)
     {
        if (eina_str_has_extension(file, ".edj") && strcmp(file, "default.edj"))
          {
             theme = malloc(sizeof(Edi_Theme));
             name = strdup(file);
             name[strlen(name) - 4] = '\0';
             theme->name = name;

             theme->path = edi_path_append(directory, file);
             _edi_themes = eina_list_append(_edi_themes, theme);
          }
        free(file);
     }

   if (files)
     eina_list_free(files);

   return _edi_themes;
}


