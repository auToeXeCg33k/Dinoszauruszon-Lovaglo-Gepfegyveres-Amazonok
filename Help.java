class Help implements Command {
  public void execute(String[] strs, World world) {}
  
  public boolean execute() {
    System.out.println("A játékban kétféle entitás létezik : amazon és dinoszaurusz.\nEbben a korai verzióban ezeknek bizonyos manipulálása lehetséges.");
    System.out.println("Az elérhető parancsok az alábbiak:");
    System.out.println("exit: most magyarázzam?");
    System.out.println("new [entitástípus] [név]: csinál egy adott típusú entitást a megadott névvel");
    System.out.println("select [név]: kiválasztja a megadott amazont");
    System.out.println("attack [név]: a kiválaszott amazon megtámadja a megadott amazont");
    System.out.println("where: a kiválasztott amazon tartózkodási helye");
    System.out.println("move [x] [y]: a kiválasztott amazon a megadott koordinátára mozdul");
    System.out.println("lookaround: a kiválasztott amazon megvizsgálja környezetét");
    System.out.println("tame [név]: a kiválasztott amazon beidomítja a megadott dinoszauruszt, ha az a környezetében van");
    System.out.println("geton: a kiválaszott amazon felszáll a dinoszauruszára");
    System.out.println("getoff: a kiválasztott amazon leszáll a dinoszauruszáról");
    return true;
  }
}
