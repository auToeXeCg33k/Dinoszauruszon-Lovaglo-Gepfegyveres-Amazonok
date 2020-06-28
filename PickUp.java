public class PickUp implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (world.getItemClassMap().get(strs[1]) != null) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                for (int k = 0; k < world.getTiles()[i][j].getItemList().size(); k++) {
                  if (((Item)world.getTiles()[i][j].getItemList().get(k)).getClass().equals(world.getItemClassMap().get(strs[1]))) {
                    if (((Select)world.getCommandMap().get("select")).getSelection().putInInventory(world.getTiles()[i][j].getItemList().get(k))) {
                      world.getTiles()[i][j].rmItem(world.getTiles()[i][j].getItemList().get(k));
                      System.out.println("Picked up " + strs[1]);
                      return;
                    } 
                    System.out.println("nem sikerült felvenni");
                    return;
                  } 
                } 
                System.out.println("ilyen nincs a közelben");
                return;
              } 
            } 
          } 
        } else {
          System.out.println("ilyen item nincs is");
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummenyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
