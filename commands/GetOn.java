package commands;

import core.Data;

public class GetOn implements Command {
  public String execute(String[] strs, Data data) {
    if (strs.length == 1) {
      if (((Select)data.getCommand("select")).getSelection() != null) {
        if (((Select)data.getCommand("select")).getSelection().getHP() > 0.0D) {
          if (((Select)data.getCommand("select")).getSelection().getDinoszaurusz() != null) {
            if (!((Select)data.getCommand("select")).getSelection().isLovagol()) {
              if (data.tileOfSelected().containsDinoszaurusz(((Select)data.getCommand("select")).getSelection().getDinoszaurusz())) {
                if (((Select)data.getCommand("select")).getSelection().getDinoszaurusz().getHP() > 0.0D) {
                  data.tileOfSelected().rmDinoszaurusz(((Select)data.getCommand("select")).getSelection().getDinoszaurusz());
                  ((Select)data.getCommand("select")).getSelection().setLovagol(true);
                  return ((Select)data.getCommand("select")).getSelection().getNev() + " felszállt a dinoszauruszra.\n";
                } 
                return "A dinó ki van múlva.\n";
              } 
              return "Nincs itt a dinó.\n";
            } 
            return ((Select)data.getCommand("select")).getSelection().getNev() + " már lovagol!\n";
          } 
          return ((Select)data.getCommand("select")).getSelection().getNev() + " amazonnak nincs dinója. Idomíts be vele egyet!\n";
        } 
        return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is él!\n";
      } 
      return "Válasszá valakit!\n";
    } 
    return "Nem megfelelő a gyökérségek száma heló!\n";
  }
}
