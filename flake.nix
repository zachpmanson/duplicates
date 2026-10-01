{
  description = "duplicates file finder";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";

  outputs = { self, nixpkgs }:
    let
      systems = [
        "aarch64-darwin"
        "x86_64-darwin"
        "aarch64-linux"
        "x86_64-linux"
      ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      packages = forAllSystems (system:
        let pkgs = nixpkgs.legacyPackages.${system};
        in {
          default = pkgs.stdenv.mkDerivation {
            pname = "duplicates";
            version = "1.0.0";
            src = ./.;

            dontConfigure = true;

            # The original coursework sources define globals in several headers;
            # retain the pre-GCC-10 common-symbol behavior they rely on.
            NIX_CFLAGS_COMPILE = "-fcommon";

            buildPhase = ''
              runHook preBuild
              make
              runHook postBuild
            '';

            installPhase = ''
              runHook preInstall
              install -Dm755 duplicates $out/bin/duplicates
              runHook postInstall
            '';
          };
        });
    };
}
