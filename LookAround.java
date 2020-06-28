public class LookAround implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
              System.out.print("Amazonok az aktuális koordinátán: ");
              for (Amazon amazon : world.getTiles()[i][j].getAmazonSet()) {
                if (amazon != ((Select)world.getCommandMap().get("select")).getSelection())
                  System.out.print(amazon.getNev() + amazon.getNev()); 
              } 
              System.out.print("\nDinoszauruszok az aktuális koordinátán: ");
              for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j].getDinoszauruszList()) {
                if (dinoszaurusz != ((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz())
                  System.out.print(dinoszaurusz); 
              } 
              System.out.print("\nItemek az aktuális koordinátán: ");
              for (Item item : world.getTiles()[i][j].getItemList()) {
                if (item != ((Select)world.getCommandMap().get("select")).getSelection().getGepFegyver())
                  System.out.print(item); 
              } 
              try {
                if (world.getTiles()[i + 1][j].exists()) {
                  System.out.print("\nAmazonok északra: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok északra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek északra: ");
                  for (Item item : world.getTiles()[i + 1][j].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j + 1].exists()) {
                  System.out.print("\nAmazonok az észak-keletre: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok észak-keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j + 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek észak-keletre: ");
                  for (Item item : world.getTiles()[i + 1][j + 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j + 1].exists()) {
                  System.out.print("\nAmazonok keletre: ");
                  for (Amazon amazon : world.getTiles()[i][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j + 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek keletre: ");
                  for (Item item : world.getTiles()[i][j + 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j + 1].exists()) {
                  System.out.print("\nAmazonok dél-keletre: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok dél-keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j + 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek dél-keletre: ");
                  for (Item item : world.getTiles()[i - 1][j + 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j].exists()) {
                  System.out.print("\nAmazonok délre: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok délre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek délre: ");
                  for (Item item : world.getTiles()[i - 1][j].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j - 1].exists()) {
                  System.out.print("\nAmazonok dél-nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok dél-nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j - 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek dél-nyugatra: ");
                  for (Item item : world.getTiles()[i - 1][j - 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j - 1].exists()) {
                  System.out.print("\nAmazonok nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j - 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek nyugatra: ");
                  for (Item item : world.getTiles()[i][j - 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j - 1].exists()) {
                  System.out.print("\nAmazonok észak-nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + amazon.getNev()); 
                  System.out.print("\nDinoszauruszok észak-nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j - 1].getDinoszauruszList())
                    System.out.print(dinoszaurusz); 
                  System.out.print("\nItemek észak-nyugatra: ");
                  for (Item item : world.getTiles()[i + 1][j - 1].getItemList())
                    System.out.print(item); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              System.out.println();
            } 
          } 
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
